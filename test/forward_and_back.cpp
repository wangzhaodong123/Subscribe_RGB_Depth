/*使机器人在空间前一米进并原路返回*/
#include "ros/ros.h" 	//ros系统最基本的头文件
#include "geometry_msgs/Twist.h"//包含了std_msgs/String消息
#include <cmath>

/*void ShutDownCallBack(const ros::SingleSubscriberPublisher& pub)
{
	int rate_zero=20;
	ros::Rate loop_rate_zero(rate_zero);
	geometry_msgs::Twist move_cmd_zero;
	move_cmd_zero.linear.x=0;
	move_cmd_zero.angular.z=0;
	pub.publish(move_cmd_zero);
	loop_rate_zero.sleep();
	pub.publish(move_cmd_zero);
	ROS_INFO(" I am stopped !");
}*/

int main(int argc,char **argv)
{
	//初始化节点，节点句柄
	ros::init( argc, argv, "forward_and_back" );
	ros::NodeHandle n;
	//定义发布者对象，更新频率
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",100);
	//ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1000,(ros::SubscriberStatusCallback)ShutDownCallBack);
	
	
	int rate=20;
	ros::Rate loop_rate(rate);
	//初始化线速度，直线距离，时间，角速度，旋转角度
	float linear_speed=0.2;
	float goal_distance=1.0;
	float linear_time=goal_distance/linear_speed;
	int linear_ticks=(int)(linear_time*rate);
	float angular_speed=1.0;
	float goal_angle=M_PI;
	float angular_time=goal_angle/angular_speed;
	int angular_ticks=(int)(angular_time*rate);
	
	//时间点
	int time_0 = 0;									//开始
	int time_1 = linear_ticks;							//去直线走完
	int time_2 = linear_ticks+3;							//信息发完
	int time_3 = linear_ticks+3+angular_ticks;					//前半圆转完
	int time_4 = linear_ticks+3+angular_ticks+3;					//信息发完
	int time_5 = linear_ticks+3+angular_ticks+3+linear_ticks;			//回直线走完
	int time_6 = linear_ticks+3+angular_ticks+3+linear_ticks+3;			//信息发完
	int time_7 = linear_ticks+3+angular_ticks+3+linear_ticks+3+angular_ticks;	//后半圆转完
	int time_8 = linear_ticks+3+angular_ticks+3+linear_ticks+3+angular_ticks+3;	//信息发完
									
	
	//进入前进后退环节
	geometry_msgs::Twist move_cmd;
	move_cmd.linear.x=0;
	move_cmd.linear.y=0;
	move_cmd.linear.z=0;
	move_cmd.angular.x=0;
	move_cmd.angular.y=0;
	move_cmd.angular.z=0;
	
	int click = 0;
	while ( ros::ok() && click <= time_8 )
	{
	  //前进
	  if ( click >= time_0 && click < time_1 )
	  {
	    if ( click == time_0 )
	    ROS_INFO(" FORWARD ");
	    move_cmd.linear.x=linear_speed;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    ros::spinOnce();
	  }
	  //发消息
	  if ( click >= time_1 && click < time_2 )
	  {
	    if ( click == time_1 )
	    ROS_INFO(" STOP ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    ros::spinOnce();
	  }
	  //旋转
	  if ( click >= time_2 && click < time_3 )
	  {
	    if ( click == time_2 )
	    ROS_INFO(" ROTATE ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=angular_speed;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    ros::spinOnce();
	  }
	  //发消息
	  if ( click >= time_3 && click < time_4 )
	  {
	    if ( click == time_3 )
	    ROS_INFO(" STOP ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    ros::spinOnce();
	  }
	  //返回
	  if ( click >= time_4 && click < time_5 )
	  {
	    if ( click == time_4 )
	    ROS_INFO(" BACK ");
	    move_cmd.linear.x=linear_speed;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    //ros::spinOnce();
	  }
	  //发消息
	  if ( click >= time_5 && click < time_6 )
	  { 
	    if ( click == time_5 )
	    ROS_INFO(" STOP ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    //ros::spinOnce();
	  }
	  //旋转
	  if ( click >= time_6 && click < time_7 )
	  {
	    //loop_rate.sleep();
	    if ( click == time_6 )
	    ROS_INFO(" ROTATE ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=angular_speed;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    //ros::spinOnce();
	  }
	  //发消息
	  if ( click >= time_7 && click < time_8 )
	  {
	    if ( click == time_7 )
	    ROS_INFO(" STOP ");
	    move_cmd.linear.x=0;
	    move_cmd.angular.z=0;
	    chatter_pub.publish(move_cmd);
	    //loop_rate.sleep();
	    //ros::spinOnce();
	  }
	  loop_rate.sleep();
	  ros::spinOnce();
	  click++;
	}
	
	ROS_INFO(" STOP ");
	move_cmd.linear.x=0;
	move_cmd.angular.z=0;
	chatter_pub.publish(move_cmd);
	
	if ( click < time_8 )
	  ROS_INFO( " STOPPED BY YOU " );
	else
	  ROS_INFO( " FINISHED " );
	
	ROS_INFO( " click == %d ",click );
	
	return 0;
}
