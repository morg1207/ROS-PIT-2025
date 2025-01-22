#!/usr/bin/env python3
import rospy
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist


def poseCallback(data):
    rospy.loginfo("La posicion de la tortuga")  

def suscriptor():
    rospy.init_node('suscriptor',anonymous=True)

    sub = rospy.Subscriber('/turtle1/pose', Pose, poseCallback)
    rospy.spin()

if __name__ == '__main__':
        try:
             suscriptor()
        except rospy.ROSInterruptException:
             pass

