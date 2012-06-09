#include "my_controller_pkg/joint_controller.h"
#include <pluginlib/class_list_macros.h>
#include <boost/thread.hpp>

namespace ik_joint_controller_ns {


	void IkJointControllerClass::getParams(ros::NodeHandle& n) {
		ROS_INFO("getting gains params and join name params");

		XmlRpc::XmlRpcValue joint_names;  //array of 7 joint names

		if (!n.getParam("joints", joint_names)){
		    ROS_ERROR("No joints given. (namespace: %s)", n.getNamespace().c_str());
		}

		if ((joint_names.getType() != XmlRpc::XmlRpcValue::TypeArray) || (joint_names.size() != 7)){
		    ROS_ERROR("Malformed joint specification.  (namespace: %s)", n.getNamespace().c_str());
		}

		std::string joint_param_ns;
		for (int i = 0; i < 7; i++){
			XmlRpc::XmlRpcValue &name_value = joint_names[i];
		    if (name_value.getType() != XmlRpc::XmlRpcValue::TypeString){
		    	ROS_ERROR("Array of joint names should contain all strings.  (namespace: %s)", n.getNamespace().c_str());
		    }
		    joint_names_[i] = ((std::string)name_value).c_str();

		    joint_param_ns = std::string("gains/") + joint_names_[i];
			n.getParam(joint_param_ns + "/p", p_[i]);
			n.getParam(joint_param_ns + "/d", d_[i]);

			ROS_INFO("NEW YAML got %d-th joint name %s with (p,d) gains parameters: (%f,%f)",
					i,
					joint_names_[i].c_str(),
					p_[i],
					d_[i]);
		}

    }


	void IkJointControllerClass::getParamsLoop(ros::NodeHandle& n) {
		while (ros::ok()) {
			getParams(n);
		}
	}


    /// Controller initialization in non-realtime
    bool IkJointControllerClass::init(pr2_mechanism_model::RobotState *robot, ros::NodeHandle &n){
    	ROS_INFO("initializing ik_joint_controller");

    	getParams(n);

        sub_ = n.subscribe("joint_command", 100, &IkJointControllerClass::jointCommandCallback, this);


        for (int i=0; i < 7; ++i)  {
            joint_states_[i] = robot->getJointState(joint_names_[i].c_str());

            if (joint_states_[i] == NULL) {
                ROS_ERROR("couldn't find joint named %s", joint_names_[i].c_str());
            }

            target_[i] = joint_states_[i]->position_;

        }
        return true;
    }

    void IkJointControllerClass::jointCommandCallback(const my_controller_pkg::JointCommand& msg){
    	ROS_INFO("ik_joint_controller got JointCommand");
        for (int i=0; i < 7; ++i) {
            target_[i] = msg.joints[i];
        }
    }


    /// Controller startup in realtime
    void IkJointControllerClass::starting(){
    	ROS_INFO("starting ik_joint_controller");

		for (int i=0; i < 7; ++i) {
		  target_[i] = joint_states_[i]->position_;
		  err_[i] = 0;
		}
    }


    /// Controller update loop in realtime
    void IkJointControllerClass::update(){
        for (int i = 0; i < 7; i++) {
          double err;
          double d_err; //error derivative

          err = (target_[i] - joint_states_[i]->position_); // current error
          d_err = 1000*(err_[i] - err);
          joint_states_[i]->commanded_effort_ =  err * p_[i] - d_err * d_[i];
          err_[i] = err;

        }
    }


    /// Controller stopping in realtime
    void IkJointControllerClass::stopping(){
    }

} // namespace

/// Register controller to pluginlib
PLUGINLIB_REGISTER_CLASS(IkJointControllerPlugin1, ik_joint_controller_ns::IkJointControllerClass, pr2_controller_interface::Controller)
