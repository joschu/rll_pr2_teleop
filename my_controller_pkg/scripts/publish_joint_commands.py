from __future__ import division
import roslib
roslib.load_manifest('rospy')
roslib.load_manifest('my_controller_pkg')
import rospy
import matplotlib.pyplot as plt
import numpy as np
from my_controller_pkg.msg import JointCommand
from sensor_msgs.msg import JointState
from time import time, sleep


joint_ind = 5

def step_function(x):
    if x < 2: return 0
    else: return 1


cmd_period = .01
sine_period = 1
total_time = 5
amplitude = -.5

cmd_times = []
cmd_vals = []

actual_vals = []
actual_times = []
stopped = True
robot_joint_index = None
joint_names = ["r_shoulder_pan_joint",
               "r_shoulder_lift_joint",
               "r_upper_arm_roll_joint",
               "r_elbow_flex_joint",
               "r_forearm_roll_joint",
               "r_wrist_flex_joint",
               "r_wrist_roll_joint"]

def joint_callback(msg):
    global robot_joint_index
    if robot_joint_index is None:
        robot_joint_index = msg.name.index(joint_names[joint_ind])
    if not stopped:
        actual_times.append(time() - t_start)
        actual_vals.append(msg.position[robot_joint_index])



rospy.init_node("publish_joint_commands",disable_signals=True)

cmd = JointCommand()
cmd.joints = [1,1,1,1,1,1,1]

pub = rospy.Publisher("/my_controller_name/joint_command", JointCommand)
sub = rospy.Subscriber("/joint_states", JointState, joint_callback)

sleep(1)

rospy.set_param("/my_controller_name/gains/p0",2400)
rospy.set_param("/my_controller_name/gains/d0",150)
rospy.set_param("/my_controller_name/gains/p1",1200)
rospy.set_param("/my_controller_name/gains/d1",100)
rospy.set_param("/my_controller_name/gains/p2",1000)
rospy.set_param("/my_controller_name/gains/d2",60)
rospy.set_param("/my_controller_name/gains/p3",700)
rospy.set_param("/my_controller_name/gains/d3",40)
rospy.set_param("/my_controller_name/gains/p4",300)
rospy.set_param("/my_controller_name/gains/d4",60)
rospy.set_param("/my_controller_name/gains/p5",300)
rospy.set_param("/my_controller_name/gains/d5",40)
rospy.set_param("/my_controller_name/gains/p6",300)
rospy.set_param("/my_controller_name/gains/d6",40)

cmd = JointCommand()
cmd.joints = np.zeros(7)
pub.publish(cmd)

print "sleeping 2 seconds"
sleep(2)
print "ok"

t_start = time()
stopped = False
while True:
    t_now = time()
    if t_now - t_start > total_time: break
    cmd = JointCommand()
    cmd.joints = np.zeros(7)
    #cmd_val = np.sin((t_now - t_start) * 2* np.pi / sine_period) * amplitude
    cmd_val = step_function(t_now - t_start) * amplitude
    cmd.joints[joint_ind] = cmd_val
    cmd_times.append(t_now - t_start)
    cmd_vals.append(cmd_val)
    pub.publish(cmd)
    sleep(cmd_period)
    

print "done"
stopped = True
plt.plot(cmd_times, cmd_vals)
plt.plot(actual_times, actual_vals)
plt.show()




