#include <pr2_controller_interface/controller.h>
#include <pr2_mechanism_model/joint.h>
#include <ros/ros.h>
#include <my_controller_pkg/JointCommand.h>

namespace ik_joint_controller_ns{

    class IkJointControllerClass: public pr2_controller_interface::Controller
    {
        private:

    		std::string joint_names_[7]; //array of 7 joint names
    		pr2_mechanism_model::JointState* joint_states_[7]; //handle on the 7 joint states

            double init_pos_;
            ros::ServiceServer srv_;
            ros::Subscriber sub_;

            void jointCommandCallback(const my_controller_pkg::JointCommand& msg);
            void getParams(ros::NodeHandle&);
            void getParamsLoop(ros::NodeHandle&);//continuously get parameters so we dont have to reload controller
            void spinFunc();// for subcriber callback

            double target_[7];  //target joint values

            double p_[7]; //proportional
            double d_[7]; //derivative

            double err_[7]; //error in the last time step

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

