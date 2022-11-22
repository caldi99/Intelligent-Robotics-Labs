#include <ros/ros.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>


//#include <apriltag_ros/AprilTagDetectionArray.h>



void callback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
{
    
    for(int i = 0; i < msg->detections.size(); i++)
    {
        apriltag_ros::AprilTagDetection det = (msg->detections)[i];
        geometry_msgs::PoseWithCovarianceStamped poseCovarianceStamped = det.pose;
        geometry_msgs::PoseWithCovariance poseCovariance = poseCovarianceStamped.pose;
        geometry_msgs::Pose pose = poseCovariance.pose;        
        ROS_INFO_STREAM(pose);        
    }
    
}

int main(int argc, char** argv)
{
    //Contact Master
    ros::init(argc,argv,"part1");

    //Start Node
    ros::NodeHandle node;

    //Subscribe
    ros::Subscriber sub = node.subscribe("tag_detections",1000, callback);

    ros::spin();

    return 0;
}