/*
 * 使用ROS节点接受并同步rgb图像和depth图像
 *
 * 回调函数也写好了，但是就是不能显示，考虑可能是内存和变量传递的问题;
 * 解决不更新显示问题的竟然是 imshow() 后面加了个 cv::waitkey ;
 * 以类的形式使用回调函数，时间同步，最终显示；
 * 将类整理到了头文件当中；
 *
 *			2018/4/3 
*/


#include <iostream>
#include <ros/ros.h>

#include "../include/ros_slam/slam_vo.h"

//测试函数
int main(int argc, char **argv)
{
  //ros节点初始化
  ros::init(argc, argv, "SLAM_VO");
  
  //节点句柄
  ros::NodeHandle nodehandle;

  //前端类对象
  SLAM_VO slam_vo(nodehandle);

  //循环等待
  ros::spin();
  ros::shutdown();

  return 0;
}