#include <pr2_controller_interface/controller.h>
#include <pr2_mechanism_model/chain.h>
#include <pr2_mechanism_model/robot.h>

#include <boost/scoped_ptr.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/jntarray.hpp>

#include <ros/ros.h>
#include <sixense/Calib.h>
#include <my_controller_pkg/MoveWithPaddle.h>

namespace ik_joint_controller_ns{

    class MyCartControllerClass: public pr2_controller_interface::Controller
    {
        private:

            bool moveWithPaddle(my_controller_pkg::MoveWithPaddle::Request& req,
                             my_controller_pkg::MoveWithPaddle::Response& resp);

            void hydraCalibCallback(const sixense::Calib& msg);

            KDL::Vector l_initial_frame_;
            KDL::Vector r_initial_frame_;
            KDL::Vector l_latest_frame_;
            KDL::Vector r_latest_frame_;
            bool lb_latest_;
            bool rb_latest_;
            
            ros::Subscriber sub_; /// = n.subscribe("chatter", 1000, chatterCallback);
            //ros::ServiceServer srv_;
            
            // The current robot state (to get the time stamp)               
            pr2_mechanism_model::RobotState* robot_state_;

            // The chain of links and joints                                 
            pr2_mechanism_model::Chain chain_;
            KDL::Chain kdl_chain_;

            // KDL Solvers performing the actual computations                
            boost::scoped_ptr<KDL::ChainFkSolverPos>    jnt_to_pose_solver_;
            boost::scoped_ptr<KDL::ChainJntToJacSolver> jnt_to_jac_solver_;

            // The variables (which need to be pre-allocated).               
            KDL::JntArray  q_;            // Joint positions                 
            KDL::JntArray  q0_;           // Joint initial positions         
            KDL::JntArrayVel  qdot_;      // Joint velocities                
            KDL::JntArray  tau_;          // Joint torques                   

            KDL::Frame     x_;            // Tip pose                        
            KDL::Frame     xd_;           // Tip desired pose                
            KDL::Frame     x0_;           // Tip initial pose                

            KDL::Twist     xerr_;         // Cart error                      
            KDL::Twist     xdot_;         // Cart velocity                   
            KDL::Wrench    F_;            // Cart effort                     
            KDL::Jacobian  J_;            // Jacobian                        

            // Note the gains are incorrectly typed as a twist,              
            // as there is no appropriate type!                              
            KDL::Twist     Kp_;           // Proportional gains              
            KDL::Twist     Kd_;           // Derivative gains                

            // The trajectory variables                                      
            double    circle_phase_;      // Phase along the circle          
            ros::Time last_time_;         // Time of the last servo cycle    

        public:
            bool init(pr2_mechanism_model::RobotState *robot,
                    ros::NodeHandle &n);
            void starting();
            void update();
            void stopping();
    };
}
