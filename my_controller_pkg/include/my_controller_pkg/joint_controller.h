#include <pr2_controller_interface/controller.h>
#include <pr2_mechanism_model/joint.h>
#include <ros/ros.h>
#include <my_controller_pkg/JointCommand.h>

namespace my_controller_ns{

    class MyControllerClass: public pr2_controller_interface::Controller
    {
        private:

    		pr2_mechanism_model::JointState* l_joint_states_[7]; //
            pr2_mechanism_model::JointState* r_joint_states_[7]; //

            double init_pos_;
            ros::ServiceServer srv_;
            ros::Subscriber sub_;

            void jointCommandCallback(const my_controller_pkg::JointCommand& msg);
            void getParams(ros::NodeHandle&);
            void getParamsLoop(ros::NodeHandle&);//continuously get parameters so we dont have to reload controller
            void spinFunc();// for subcriber callback

            double l_target_[7];  //target joint values for left arm
            double r_target_[7];  //target joint values for right arm

            double p_[7]; //proportional
            double d_[7]; //derivative

            double l_err_[7]; //error in the last time step for left arm
            double r_err_[7]; //error in the last time step for right arm

            //current robot state to get time stamp
            pr2_mechanism_model::RobotState* robot_state_;


        public:
            virtual bool init(pr2_mechanism_model::RobotState *robot,
                    ros::NodeHandle &n);
            virtual void starting();
            virtual void update();
            virtual void stopping();
    };
} 

