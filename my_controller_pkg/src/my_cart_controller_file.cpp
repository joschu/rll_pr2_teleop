#include "my_controller_pkg/my_cart_controller_file.h"
#include <pluginlib/class_list_macros.h>

using namespace my_controller_ns;


/// Controller initialization in non-realtime                                                                                                                                     
bool MyCartControllerClass::init(pr2_mechanism_model::RobotState *robot,
        ros::NodeHandle &n)
{
    ROS_INFO("INIT CARTCONTROLLER");
    // Get the root and tip link names from parameter server.            
    std::string root_name, tip_name;
    if (!n.getParam("root_name", root_name))
    {
        ROS_ERROR("No root name given in namespace: %s)",
                n.getNamespace().c_str());
        return false;
    }
    if (!n.getParam("tip_name", tip_name))
    {
        ROS_ERROR("No tip name given in namespace: %s)",
                n.getNamespace().c_str());
        return false;
    }

    // Construct a chain from the root to the tip and prepare the kinematics.         
    // Note the joints must be calibrated.                                            
    if (!chain_.init(robot, root_name, tip_name))
    {
        ROS_ERROR("MyCartController could not use the chain from '%s' to '%s'",
                root_name.c_str(), tip_name.c_str());
        return false;
    }

    // Store the robot handle for later use (to get time).                            
    robot_state_ = robot;

    // Construct the kdl solvers in non-realtime.                                     
    chain_.toKDL(kdl_chain_);
    jnt_to_pose_solver_.reset(new KDL::ChainFkSolverPos_recursive(kdl_chain_));
    jnt_to_jac_solver_.reset(new KDL::ChainJntToJacSolver(kdl_chain_));

    // Resize (pre-allocate) the variables in non-realtime.                           
    q_.resize(kdl_chain_.getNrOfJoints());
    q0_.resize(kdl_chain_.getNrOfJoints());
    qdot_.resize(kdl_chain_.getNrOfJoints());
    tau_.resize(kdl_chain_.getNrOfJoints());
    J_.resize(kdl_chain_.getNrOfJoints());

    // Pick the gains.                                                                
    Kp_.vel(0) = 100.0;  Kd_.vel(0) = 1.0;        // Translation x                    
    Kp_.vel(1) = 100.0;  Kd_.vel(1) = 1.0;        // Translation y                    
    Kp_.vel(2) = 100.0;  Kd_.vel(2) = 1.0;        // Translation z                    
    Kp_.rot(0) = 100.0;  Kd_.rot(0) = 1.0;        // Rotation x                       
    Kp_.rot(1) = 100.0;  Kd_.rot(1) = 1.0;        // Rotation y                       
    Kp_.rot(2) = 100.0;  Kd_.rot(2) = 1.0;        // Rotation z                       

    //srv_ = n.advertiseService("move_with_paddle", &MyCartControllerClass::moveWithPaddle, this);
    ROS_INFO("trying to instantiate subscriber");
    sub_ = n.subscribe("hydra_calib", 1000, &MyCartControllerClass::hydraCalibCallback, this);
    ROS_INFO("instantiated subscriber");
    l_initial_frame_ = KDL::Vector(0,0,0); 
    r_initial_frame_ = KDL::Vector(0,0,0);
    l_latest_frame_ = KDL::Vector(0,0,0); 
    r_latest_frame_ = KDL::Vector(0,0,0);
    lb_latest_ = false;
    rb_latest_ = false; 
    return true;
}

void MyCartControllerClass::hydraCalibCallback(const sixense::Calib& msg){
    bool rb_current = msg.paddles[1].buttons[5];

    float r_x = msg.paddles[1].transform.translation.x;
    float r_y = msg.paddles[1].transform.translation.y;
    float r_z = msg.paddles[1].transform.translation.z;

    ROS_INFO("MyCartController: reading paddle update");
    ROS_INFO("paddle1 x,y,z: %f,%f,%f", r_x, r_y, r_z);
    
    if (rb_current == false) {
        r_initial_frame_ = KDL::Vector(0,0,0); 
        r_latest_frame_ = KDL::Vector(0,0,0); 
    } else if (rb_latest_ == false){
        r_initial_frame_ = KDL::Vector(r_x, r_y, r_z); 
        r_latest_frame_  = KDL::Vector(r_x, r_y, r_z); 
    } else{
        r_latest_frame_  = KDL::Vector(r_x, r_y, r_z); 
    }
    
    rb_latest_ = rb_current;
}



/// Controller startup in realtime                                                   
void MyCartControllerClass::starting()
{
    // Get the current joint values to compute the initial tip location.              
    chain_.getPositions(q0_);
    jnt_to_pose_solver_->JntToCart(q0_, x0_);

    // Initialize the phase of the circle as zero.                                    
    circle_phase_ = 0.0;

    // Also reset the time-of-last-servo-cycle.                                       
    last_time_ = robot_state_->getTime();
}


/// Controller update loop in realtime                                               
void MyCartControllerClass::update()
{
    double dt;                    // Servo loop time step                             

    // Calculate the dt between servo cycles.                                         
    dt = (robot_state_->getTime() - last_time_).toSec();
    last_time_ = robot_state_->getTime();

    // Get the current joint positions and velocities.                                
    chain_.getPositions(q_);
    chain_.getVelocities(qdot_);

    // Compute the forward kinematics and Jacobian (at this location).                
    jnt_to_pose_solver_->JntToCart(q_, x_);
    jnt_to_jac_solver_->JntToJac(q_, J_);

    for (unsigned int i = 0 ; i < 6 ; i++)
    {
        xdot_(i) = 0;
        for (unsigned int j = 0 ; j < kdl_chain_.getNrOfJoints() ; j++)
            xdot_(i) += J_(i,j) * qdot_.qdot(j);
    }
    
    //move in direction of paddle differece
    KDL::Vector r_paddle_change = r_latest_frame_ - r_initial_frame_;
    r_paddle_change(0) = r_paddle_change(0) * dt;
    r_paddle_change(1) = r_paddle_change(1) * dt;
    r_paddle_change(2) = r_paddle_change(2) * dt;

    // Follow a circle of 10cm at 3 rad/sec.                                          
    /**
    circle_phase_ += 3.0 * dt;
    KDL::Vector  circle(0,0,0);
    circle(2) = 0.1 * sin(circle_phase_);
    circle(1) = 0.1 * (cos(circle_phase_) - 1);
    **/

    xd_ = x0_;
    //xd_ = x_;
    //xd_.p += circle;
    xd_.p += r_paddle_change;

    // Calculate a Cartesian restoring force.                                         
    xerr_.vel = x_.p - xd_.p;
    xerr_.rot = 0.5 * (xd_.M.UnitX() * x_.M.UnitX() +
            xd_.M.UnitY() * x_.M.UnitY() +
            xd_.M.UnitZ() * x_.M.UnitZ());

    for (unsigned int i = 0 ; i < 6 ; i++)
        F_(i) = - Kp_(i) * xerr_(i) - Kd_(i) * xdot_(i);

    // Convert the force into a set of joint torques.                                 
    for (unsigned int i = 0 ; i < kdl_chain_.getNrOfJoints() ; i++)
    {
        tau_(i) = 0;
        for (unsigned int j = 0 ; j < 6 ; j++)
            tau_(i) += J_(j,i) * F_(j);
    }

    // And finally send these torques out.                                            
    chain_.setEfforts(tau_);
}


/// Controller stopping in realtime                                                  
void MyCartControllerClass::stopping()
{}

bool MyCartControllerClass::moveWithPaddle(my_controller_pkg::MoveWithPaddle::Request& req, my_controller_pkg::MoveWithPaddle::Response& resp){
    //req is a sixense/Calib msg

    bool lb_current = req.calib.paddles[0].buttons[5];
    bool rb_current = req.calib.paddles[1].buttons[5];

    float l_x = req.calib.paddles[0].transform.translation.x;
    float l_y = req.calib.paddles[0].transform.translation.y;
    float l_z = req.calib.paddles[0].transform.translation.z;
    float r_x = req.calib.paddles[1].transform.translation.x;
    float r_y = req.calib.paddles[1].transform.translation.y;
    float r_z = req.calib.paddles[1].transform.translation.z;

    ROS_INFO("MyCartController: reading paddle update");
    ROS_INFO("paddle0 x,y,z: %f,%f,%f", req.calib.paddles[0].transform.translation.x,
                                        req.calib.paddles[0].transform.translation.y,
                                        req.calib.paddles[0].transform.translation.z);
    ROS_INFO("paddle1 x,y,z: %f,%f,%f", req.calib.paddles[1].transform.translation.x,
                                        req.calib.paddles[1].transform.translation.y,
                                        req.calib.paddles[1].transform.translation.z);

    if (lb_current == false) {
        l_initial_frame_ = KDL::Vector(0,0,0); 
        l_latest_frame_ = KDL::Vector(0,0,0); 
    } else if (lb_latest_ == false){
        l_initial_frame_ = KDL::Vector(l_x, l_y, l_z); 
        l_latest_frame_  = KDL::Vector(l_x, l_y, l_z); 
    } else{
        l_latest_frame_  = KDL::Vector(l_x, l_y, l_z); 
    }

    
    if (rb_current == false) {
        r_initial_frame_ = KDL::Vector(0,0,0); 
        r_latest_frame_ = KDL::Vector(0,0,0); 
    } else if (rb_latest_ == false){
        r_initial_frame_ = KDL::Vector(r_x, r_y, r_z); 
        r_latest_frame_  = KDL::Vector(r_x, r_y, r_z); 
    } else{
        r_latest_frame_  = KDL::Vector(r_x, r_y, r_z); 
    }
    
    lb_latest_ = lb_current;
    rb_latest_ = rb_current;

    resp.resp = true; 
    return true;
}


/// Register controller to pluginlib                                                 
PLUGINLIB_REGISTER_CLASS(MyCartControllerPlugin,
        my_controller_ns::MyCartControllerClass,
        pr2_controller_interface::Controller)
