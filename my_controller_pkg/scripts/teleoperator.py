from __future__ import division
import roslib
roslib.load_manifest('rospy')
roslib.load_manifest('my_controller_pkg')
import rospy
import matplotlib.pyplot as plt
import numpy as np
from my_controller_pkg.msg import JointCommand
from sensor_msgs.msg import JointState
from geometry_msgs.msg import PoseStamped
from time import time, sleep

def callback(msg):
    pass

joint_pub = rospy.Publisher("/my_controller_name/joint_command", JointCommand)
command_pub = rospy.Publisher("/cart_target", PoseStamped)
sub = rospy.Subscriber("/hydra_message", JointState, joint_callback)

