#include "my_controller_pkg/joint_controller.h"
#include <pluginlib/class_list_macros.h>
#include <boost/thread.hpp>

namespace ik_joint_controller_ns {


	void IkJointControllerClass::getParams(ros::NodeHandle& n) {
		ROS_INFO("getting params for ik_joint_controller");
    	n.getParam("gains/p0", p_[0]);
    	n.getParam("gains/p1", p_[1]);
    	n.getParam("gains/p2", p_[2]);
    	n.getParam("gains/p3", p_[3]);
    	n.getParam("gains/p4", p_[4]);
    	n.getParam("gains/p5", p_[5]);
    	n.getParam("gains/p6", p_[6]);

    	n.getParam("gains/d0", d_[0]);
    	n.getParam("gains/d1", d_[1]);
    	n.getParam("gains/d2", d_[2]);
    	n.getParam("gains/d3", d_[3]);
    	n.getParam("gains/d4", d_[4]);
    	n.getParam("gains/d5", d_[5]);
    	n.getParam("gains/d6", d_[6]);

    	for (int i = 0 ; i < 7; i++){
			ROS_INFO("got gains parameter p %d:%f",i , p_[i]);
			ROS_INFO("got gains parameter d %d:%f",i , d_[i]);
    	}
    }

	void IkJointControllerClass::getParamsLoop(ros::NodeHandle& n) {
		while (ros::ok()) {
			getParams(n);
		}
	}


	void IkJointControllerClass::spinFunc() {
		ros::spin();
	}

    /// Controller initialization in non-realtime
    bool IkJointControllerClass::init(pr2_mechanism_model::RobotState *robot,
            ros::NodeHandle &n)
    {
    	ROS_INFO("initializing ik_joint_controller");

    	getParams(n);
    	//boost::thread(&IkJointControllerClass::getParamsLoop, this, n);

        char* r_joint_names[] = {"r_shoulder_pan_joint",
                                "r_shoulder_lift_joint",
                                "r_upper_arm_roll_joint",
                                "r_elbow_flex_joint",
                                "r_forearm_roll_joint",
                                "r_wrist_flex_joint",
                                "r_wrist_roll_joint"};

        char* l_joint_names[] = {"l_shoulder_pan_joint",
                                "l_shoulder_lift_joint",
                                "l_upper_arm_roll_joint",
                                "l_elbow_flex_joint",
                                "l_forearm_roll_joint",
                                "l_wrist_flex_joint",
                                "l_wrist_roll_joint"};

        sub_ = n.subscribe("joint_command", 100, &IkJointControllerClass::jointCommandCallback, this);


        for (int i=0; i < 7; ++i)  {
        	l_joint_states_[i] = robot->getJointState(l_joint_names[i]);
            r_joint_states_[i] = robot->getJointState(r_joint_names[i]);

            if (l_joint_states_[i] == NULL) {
                ROS_ERROR("couldn't find joint named %s", l_joint_names[i]);
            }
            if (r_joint_states_[i] == NULL) {
                ROS_ERROR("couldn't find joint named %s", r_joint_names[i]);
            }

            l_target_[i] = l_joint_states_[i]->position_;
            r_target_[i] = r_joint_states_[i]->position_;

        }
        return true;
    }

    void IkJointControllerClass::jointCommandCallback(const my_controller_pkg::JointCommand& msg){
    	ROS_INFO("ik_joint_controller got JointCommand");
        for (int i=0; i < 7; ++i) {
            l_target_[i] = msg.joints[i];
            r_target_[i] = msg.joints[i+7];
        }
    }


    /// Controller startup in realtime
    void IkJointControllerClass::starting()
    {
    	ROS_INFO("starting ik_joint_controller");


    	//boost::thread(&IkJointControllerClass::spinFunc, this);

      for (int i=0; i < 7; ++i) {
    	  l_target_[i] = l_joint_states_[i]->position_;
    	  r_target_[i] = r_joint_states_[i]->position_;
    	  l_err_[i] = 0;
    	  r_err_[i] = 0;
      }
    }


    /// Controller update loop in realtime
    void IkJointControllerClass::update()
    {
        for (int i = 0; i < 7; i++) {
          double err;
          double d_err;

          err = (l_target_[i] - l_joint_states_[i]->position_); // current error
          d_err = 1000*(l_err_[i] - err);
          l_joint_states_[i]->commanded_effort_ =  err * p_[i] - d_err * d_[i];
          l_err_[i] = err;

          err = (r_target_[i] - r_joint_states_[i]->position_); // current error
          d_err = 1000*(r_err_[i] - err);
          r_joint_states_[i]->commanded_effort_ =  err * p_[i] - d_err * d_[i];
          r_err_[i] = err;

        }
    }


    /// Controller stopping in realtime
    void IkJointControllerClass::stopping()
    {}


    /// Service call to set amplitude of sin
} // namespace

/// Register controller to pluginlib
PLUGINLIB_REGISTER_CLASS(IkJointControllerPlugin,
        ik_joint_controller_ns::IkJointControllerClass,
        pr2_controller_interface::Controller)
