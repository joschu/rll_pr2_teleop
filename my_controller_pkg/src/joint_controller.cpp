#include "my_controller_pkg/joint_controller.h"
#include <pluginlib/class_list_macros.h>
#include <boost/thread.hpp>

namespace my_controller_ns {


	void MyControllerClass::getParams(ros::NodeHandle& n) {

    	n.getParam("/my_controller_name/gains/p0", p_[0]);
    	n.getParam("/my_controller_name/gains/p1", p_[1]);
    	n.getParam("/my_controller_name/gains/p2", p_[2]);
    	n.getParam("/my_controller_name/gains/p3", p_[3]);
    	n.getParam("/my_controller_name/gains/p4", p_[4]);
    	n.getParam("/my_controller_name/gains/p5", p_[5]);
    	n.getParam("/my_controller_name/gains/p6", p_[6]);

    	n.getParam("/my_controller_name/gains/d0", d_[0]);
    	n.getParam("/my_controller_name/gains/d1", d_[1]);
    	n.getParam("/my_controller_name/gains/d2", d_[2]);
    	n.getParam("/my_controller_name/gains/d3", d_[3]);
    	n.getParam("/my_controller_name/gains/d4", d_[4]);
    	n.getParam("/my_controller_name/gains/d5", d_[5]);
    	n.getParam("/my_controller_name/gains/d6", d_[6]);

	}

	void MyControllerClass::getParamsLoop(ros::NodeHandle& n) {
		while (ros::ok()) {
			getParams(n);
		}
	}
	void MyControllerClass::spinFunc() {
		ros::spin();
	}

    /// Controller initialization in non-realtime
    bool MyControllerClass::init(pr2_mechanism_model::RobotState *robot,
            ros::NodeHandle &n)
    {
    	ROS_INFO("init");

    	getParams(n);
    	boost::thread(&MyControllerClass::getParamsLoop, this, n);

        char* joint_names[] = {"r_shoulder_pan_joint",
                                "r_shoulder_lift_joint",
                                "r_upper_arm_roll_joint",
                                "r_elbow_flex_joint",
                                "r_forearm_roll_joint",
                                "r_wrist_flex_joint",
                                "r_wrist_roll_joint"};

        sub_ = n.subscribe("joint_command", 100, &MyControllerClass::jointCommandCallback, this);
        for (int i=0; i < 7; ++i)  {
            joint_states_[i] = robot->getJointState(joint_names[i]);
            if (joint_states_[i] == NULL) {
                ROS_ERROR("couldn't find joint named %s", joint_names[i]);
            }
            target_[i] = joint_states_[i]->position_;


        }
        return true;
    }

    void MyControllerClass::jointCommandCallback(const my_controller_pkg::JointCommand& msg){
    	ROS_INFO("got some joints");
        for (int i=0; i < 7; ++i) {
            target_[i] = msg.joints[i];
        }

    }


    /// Controller startup in realtime
    void MyControllerClass::starting()
    {
    	ROS_INFO("starting");
    	boost::thread(&MyControllerClass::spinFunc, this);

      for (int i=0; i < 7; ++i) {
    	  target_[i] = joint_states_[i]->position_;
    	  err_[i] = 0;
      }
    }


    /// Controller update loop in realtime
    void MyControllerClass::update()
    {
        for (int i = 0; i < 7; i++) {
          double err = (target_[i] - joint_states_[i]->position_); // current error
          double derr = 1000*(err_[i] - err);
          joint_states_[i]->commanded_effort_ =  err * p_[i] - derr * d_[i];
          err_[i] = err;
        }
    }


    /// Controller stopping in realtime
    void MyControllerClass::stopping()
    {}


    /// Service call to set amplitude of sin
} // namespace

/// Register controller to pluginlib
PLUGINLIB_REGISTER_CLASS(MyControllerPlugin1,
        my_controller_ns::MyControllerClass,
        pr2_controller_interface::Controller)