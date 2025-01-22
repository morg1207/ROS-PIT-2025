#include "ros/ros.h"
#include "turtlesim/Pose.h"


turtlesim::Pose pose_turtle;

void poseCallback(const turtlesim::Pose::ConstPtr& msg){

    pose_turtle.x = msg->x;
    pose_turtle.y = msg->y;
    
    ROS_INFO("Se la posicion de  la tortuga en x = [%.3f] y = [%.3f]",pose_turtle.x,pose_turtle.y);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "nodo_suscriptor");

  ROS_INFO("Se inicializo el nodo suscriptor");
  ros::NodeHandle n;
  ros::Subscriber pose_sub = n.subscribe("/turtle1/pose",10, poseCallback);

  //ros::spin();
  ROS_INFO("Despues del spin");
  return 0;
}