#!/usr/bin/env python
from  brett2.PR2 import PR2, IKFail
import rospy
import roslib
import utils.conversions as conv
import utils.transformations
from kinematics import kinematics_utils
roslib.load_manifest("sixense")
roslib.load_manifest("my_controller_pkg")
from hydra_msgs.msg import Calib
from my_controller_pkg.msg import JointCommand

START=0
BUMPER = 5
JOYSTICK = 6

class HydraTeleop:
    scale = .001
    xoffset = 1.
    yoffset = 0
    zoffset = 0
    last_msg = None
    counter = 0
    def __init__(self):
        self.pr2 =PR2()
        self.pr2.wait=False
        self.hydra_sub = rospy.Subscriber("hydra_calib", Calib, self.callback, buff_size=3)
        self.arms = [self.pr2.larm, self.pr2.rarm]
        self.grippers = [self.pr2.lgrip, self.pr2.rgrip]

        self.joint_pub = rospy.Publisher("/my_controller_name/joint_command", JointCommand)


    def callback(self,msg):
        self.counter+= 1
        if self.counter % 20 != 0: 
            return
        
        if self.last_msg is None: 
            self.last_msg = msg
            return

        for i in xrange(2):
            paddle = msg.paddles[i]

            if (paddle.trigger>.5) and not (self.last_msg.paddles[i].trigger>.5):
                xcur, ycur, zcur = self.arms[i].get_pose_matrix("torso_lift_link", "%s_gripper_tool_frame"%self.arms[i].lr)[:3,3]
                xcmd, ycmd, zcmd = (paddle.transform.translation.x * self.scale,
                                    paddle.transform.translation.y * self.scale,
                                    paddle.transform.translation.z * self.scale)

                self.xoffset, self.yoffset, self.zoffset = xcur-xcmd, ycur-ycmd, zcur-zcmd

                print "engaging %s arm"%self.arms[i].lr


            elif (paddle.trigger>.5) and (self.last_msg.paddles[i].trigger > .5):
                x = paddle.transform.translation.x * self.scale + self.xoffset
                y = paddle.transform.translation.y * self.scale + self.yoffset
                z = paddle.transform.translation.z * self.scale + self.zoffset

                xx = paddle.transform.rotation.x
                yy = paddle.transform.rotation.y
                zz = paddle.transform.rotation.z
                ww = paddle.transform.rotation.w

                joint_msg = JointCommand()
                mat4 = conv.trans_rot_to_hmat([x,y,z], [xx,yy,zz,ww])
                #print mat4
                cur_joints = self.arms[i].get_joint_positions()
                ik_joints = self.arms[i].cart_to_joint(mat4, "torso_lift_link", "r_gripper_tool_frame",filter_options=18)
                
                
                self.arms[i].set_cart_target([xx,yy,zz,ww], [x,y,z], "torso_lift_link")
                if ik_joints is not None:
                    ik_joints_unrolled = kinematics_utils.closer_joint_angles(ik_joints, cur_joints)
                    joint_msg.joints = ik_joints_unrolled
                    self.joint_pub.publish(joint_msg)
                    print "ik succeeded"
                else:
                    print "ik failed"

                #mat = transformations.quaternion_matrix([xx,yy,zz,ww])
                #mat[:3,3] = [x,y,z]
                #try: self.arms[i].goto_pose_matrix(mat, "torso_lift_link", self.arms[i].tool_frame);
                #except IKFail: print "%s ik failed"%self.arms[i].lrlong
                #self.grippers[i].set_angle_goal(.08*(1-paddle.trigger))

            if paddle.buttons[1]: self.grippers[i].set_angle_goal(0)
            if paddle.buttons[2]: self.grippers[i].set_angle_goal(.08)

        if (msg.paddles[1].joy[0] > 0) or (msg.paddles[1].joy[1] > 0):
            if msg.paddles[0].buttons[START]:
                pan,tilt = self.pr2.head.get_joint_positions()
                pan += .1*msg.paddles[1].joy[0]
                tilt += .15*msg.paddles[1].joy[1]
                self.pr2.head.set_pan_tilt(pan,tilt)
            else:
                self.pr2.base.set_twist((.1*msg.paddles[1].joy[1], -.1*msg.paddles[1].joy[0], msg.paddles[0].joy[0]))

        self.last_msg = msg

if __name__ == "__main__":
    rospy.init_node("pr2_hydra_teleop",disable_signals=True)
    HT = HydraTeleop()
    rospy.spin()
