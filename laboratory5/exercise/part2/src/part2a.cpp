#include <ros/ros.h>

//APRILTAG
#include <apriltag_ros/AprilTagDetectionArray.h>

//GEOMETRY MSGS
#include <geometry_msgs/PoseWithCovariance.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Pose.h>

//OPENCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

//SENSOR MSGS
#include <sensor_msgs/CameraInfo.h>

//VARIABLES

cv::Mat cameraMatrix = cv::Mat(3,3,CV_64FC1);
std::vector<double> distCoeffs;
cv::Mat image;




void callback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
{
    
    geometry_msgs::Pose avgPose;
    std::vector<cv::Point3f> objectPoints;

    for(int i = 0; i < msg->detections.size(); i++)
    {
        apriltag_ros::AprilTagDetection det = (msg->detections)[i];
        geometry_msgs::PoseWithCovarianceStamped poseCovarianceStamped = det.pose;
        geometry_msgs::PoseWithCovariance poseCovariance = poseCovarianceStamped.pose;
        geometry_msgs::Pose pose = poseCovariance.pose;        

        //Add points
        objectPoints.push_back(cv::Point3f(pose.position.x,pose.position.y,pose.position.z));

        avgPose.position.x += pose.position.x;
        avgPose.position.y += pose.position.y;
        avgPose.position.z += pose.position.z;

        avgPose.orientation.x += pose.orientation.x;
        avgPose.orientation.y += pose.orientation.y;
        avgPose.orientation.z += pose.orientation.z;
        avgPose.orientation.w += pose.orientation.w;        
    }

    //Compute avarage
    avgPose.position.x /= msg->detections.size();
    avgPose.position.y /= msg->detections.size();
    avgPose.position.z /= msg->detections.size();

    avgPose.orientation.x /= msg->detections.size();
    avgPose.orientation.y /= msg->detections.size();
    avgPose.orientation.z /= msg->detections.size();
    avgPose.orientation.w /= msg->detections.size();
    

    ROS_INFO_STREAM("AVG POSE \n");
    ROS_INFO_STREAM(avgPose);

    cv::Mat rvec = (cv::Mat_<float>(3,1) << 0.0, 0.0, 0.0);
    cv::Mat tvec = (cv::Mat_<float>(3,1) << avgPose.position.x, avgPose.position.y, avgPose.position.z);

    try
    {
        std::vector<cv::Point2f> outputPoints;        
        cv::projectPoints(objectPoints,rvec,tvec,cameraMatrix,distCoeffs,outputPoints);
        int r = (int)outputPoints.at(0).y;
        int c = (int)outputPoints.at(0).x;
        ROS_INFO_STREAM("COORDINATES \n");
        ROS_INFO_STREAM(r);
        ROS_INFO_STREAM(c);

        image.at<cv::Vec3b>(r,c) = cv::Vec3b(255,255,255);

        
        cv::imshow("Image",image);
        cv::waitKey();

    }
    catch(const cv::Exception& e)
    {
        std::cout << e.err;
    }

}



int main(int argc, char** argv)
{
    //Contact Master
    ros::init(argc,argv,"part2");

    //Start Node
    ros::NodeHandle node;

    //Subscribe
    sensor_msgs::CameraInfoConstPtr msg = ros::topic::waitForMessage<sensor_msgs::CameraInfo>("/kinect/rgb/camera_info");
    
    //Save values    
    int index = 0;
    for(int r = 0; r < 3; r++)
    {
        for(int c = 0; c < 3; c++)
        {                        
            cameraMatrix.at<double>(r,c) = (msg->K)[index++];
        }
    }
    distCoeffs.insert(distCoeffs.begin(),msg->D.begin(),msg->D.end());

    //Read image
    image = cv::imread("image_final.png",cv::IMREAD_COLOR);   
    cv::imshow("Image",image);
    cv::waitKey();

    //Subscribe
    ros::Subscriber sub = node.subscribe("tag_detections",1000, callback);

    ros::spin();

    return 0;
}