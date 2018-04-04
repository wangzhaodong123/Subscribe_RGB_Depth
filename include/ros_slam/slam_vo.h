/*
 * SLAM_VO的核心类头文件
 */

#ifndef SLAM_VO_H
#define SLAM_VO_H

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>  

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

//SLAM_VO类
class SLAM_VO
{
private:
  //统计回调次数的变量
  int count;
  
  //ros节点句柄
  ros::NodeHandle nodehandle;
  
  //定义两个分别订阅深度图和彩色图的对象
  message_filters::Subscriber<sensor_msgs::Image>* rgb_sub;
  message_filters::Subscriber<sensor_msgs::Image>* depth_sub;
  
  //消息滤波器，进行时间同步
  message_filters::Synchronizer<message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image>>* sync;

public:
  //构造函数
  SLAM_VO(const ros::NodeHandle nd);
  
  //析构函数
  ~SLAM_VO();
  
  //用于处理图片信息的回调函数
  void ImageCallback(const sensor_msgs::ImageConstPtr& msgRGB,const sensor_msgs::ImageConstPtr& msgD);
};

#endif