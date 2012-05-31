#!/usr/bin/python
import roslib
roslib.load_manifest("my_controller_pkg")
import rospy
from sixense.msg import Calib
from my_controller_pkg.srv import *

def hydra_callback(data):
    try:
        move_srv = rospy.ServiceProxy('/my_cart_controller_name/move_with_paddle', MoveWithPaddle)
        resp1 = move_srv(data)
        print "called serivce:", resp1
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def hydra_listener():
    rospy.init_node('hydra_listener')
    print "init hydra_listener"
    print "waiting for move with paddle service"
    rospy.wait_for_service('/my_cart_controller_name/move_with_paddle')
    
    rospy.Subscriber("hydra_calib", Calib, hydra_callback)
    print "init hydra_calib subscriber"
    rospy.spin()

if __name__ == '__main__':
    hydra_listener()
