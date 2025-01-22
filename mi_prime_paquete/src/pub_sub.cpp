#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

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
  
  // declaro publicadores y suscriptores
  ros::Subscriber pose_sub = n.subscribe("/turtle1/pose",10, poseCallback);
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

   //loop rate
  ros::Rate loop_rate(10);

  geometry_msgs::Twist cmd_vel_msg;

  cmd_vel_msg.linear.x = 0.5;
  cmd_vel_msg.angular.z = 0.5;
 
  while (ros::ok())
  {
    ROS_INFO("Publicando velocidad");

    cmd_vel_pub.publish(cmd_vel_msg);

    ros::spinOnce();
    loop_rate.sleep();
  }


  //ros::spin();
  ROS_INFO("Despues del spin");
  return 0;
}