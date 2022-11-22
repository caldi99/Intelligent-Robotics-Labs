#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf2_listener");

    ros::NodeHandle node;

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    geometry_msgs::TransformStamped transformStamped;
    try
    {
        transformStamped = tfBuffer.lookupTransform("camera_base", "base_link",ros::Time(0),ros::Duration(1.0)); //Duration is mandatory
        ROS_INFO_STREAM(transformStamped.transform);  
    }
    catch (tf2::TransformException &ex) 
    {
        ROS_WARN("%s",ex.what());      
    }
    return 0; 
}