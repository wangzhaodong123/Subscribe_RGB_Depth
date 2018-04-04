/*使机器人旋转*/
#include "ros/ros.h" 	//ros系统最基本的头文件
#include "geometry_msgs/Twist.h"//包含了std_msgs/String消息
#include <cmath>

int main(int argc,char **argv)
{
	//初始化节点，节点句柄
	ros::init( argc, argv, "rotation" );
	ros::NodeHandle n;
	//定义发布者对象，更新频率
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",100);
	
	int rate=20;
	ros::Rate loop_rate(rate);
	float angular_speed=1.0;
	float goal_angle=M_PI*2;
	float angular_time=goal_angle/angular_speed;
	int angular_ticks=(int)(angular_time*rate);
	
	geometry_msgs::Twist move_cmd;
	move_cmd.linear.x=0;
	move_cmd.linear.y=0;
	move_cmd.linear.z=0;
	move_cmd.angular.x=0;
	move_cmd.angular.y=0;
	move_cmd.angular.z=0;
	
	
	int i = 0;
	while ( ros::ok() && i < angular_ticks )
	{
	  move_cmd.linear.x=0;
	  move_cmd.angular.z=angular_speed;
	  chatter_pub.publish(move_cmd);
	  loop_rate.sleep();
	  ros::spinOnce();
	}
	
	ROS_INFO(" STOP ");
	move_cmd.linear.x=0;
	move_cmd.angular.z=0;
	chatter_pub.publish(move_cmd);
	
	return 0;
}