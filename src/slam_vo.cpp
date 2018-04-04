/*
 * SLAM_VO的核心类源文件
 */

#include "../include/ros_slam/slam_vo.h"

using namespace std;
using namespace cv;

//构造函数，创建两个原始窗口
SLAM_VO::SLAM_VO( const ros::NodeHandle nd ):nodehandle(nd)
{
  //回调次数置一
  count = 0;
  
  //创建两个显示窗口
  cv::namedWindow("DEPTH",CV_WINDOW_AUTOSIZE);
  cv::namedWindow("RGB",CV_WINDOW_AUTOSIZE);
    
  //实例化对象，分别订阅rgb和depth话题
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> sync_pol;
  rgb_sub = new message_filters::Subscriber<sensor_msgs::Image>(nodehandle, "/camera/rgb/image_color", 1);
  depth_sub = new message_filters::Subscriber<sensor_msgs::Image>(nodehandle, "camera/depth_registered/image_raw", 1);
  
  //回调函数为本类的一个成员函数
  sync = new message_filters::Synchronizer<sync_pol>(sync_pol(10), *rgb_sub,*depth_sub);
  sync->registerCallback(boost::bind(&SLAM_VO::ImageCallback,this,_1,_2));

};

//析构函数，删除两个窗口
SLAM_VO::~SLAM_VO()
{
  cv::destroyWindow("RGB");
  cv::destroyWindow("DEPTH");
};

//回调函数，处理时间同步后的图片
void SLAM_VO::ImageCallback(const sensor_msgs::ImageConstPtr& msgRGB, const sensor_msgs::ImageConstPtr& msgD)
{
  //将ros下的图像转换到opencv下
  //cv_bridge对象
  cv_bridge::CvImagePtr cv_ptrRGB;
  //类型转换
  try
  {
    cv_ptrRGB = cv_bridge::toCvCopy(msgRGB,sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  cv_bridge::CvImagePtr cv_ptrD;
  try
  {
    cv_ptrD = cv_bridge::toCvCopy(msgD,sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }  
  
  //显示
  Mat image_rgb = cv_ptrRGB->image.clone();  
  Mat image_depth = cv_ptrD->image.clone();
  imshow("RGB",cv_ptrRGB->image);
  cv::waitKey(1);
  imshow("DEPTH",cv_ptrD->image);
  cv::waitKey(1);

  //统计次数
  count++;
  //cout<<"第"<<count<<"进入回调函数；"<<endl;
}