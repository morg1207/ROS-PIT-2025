#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist


def publicador():
    rospy.init_node('publicador',anonymous=True)
    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    rate = rospy.Rate(10)
    cmd_vel_msg = Twist()
    cmd_vel_msg.linear.x = 0.5
    cmd_vel_msg.angular.z = 0.5
    
    while not rospy.is_shutdown():
        pub.publish(cmd_vel_msg)
        rospy.loginfo('Publicando')
        rate.sleep()

if __name__ == '__main__':
        try:
             publicador()
        except rospy.ROSInterruptException:
             pass

