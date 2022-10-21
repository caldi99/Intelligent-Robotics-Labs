#include "ros/ros.h"
#include "std_msgs/String.h"

//This is an example on how to create a Subscriber node.


void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
    //To create a node you need to use ros::init where the parameters to be passed are :
    //argc and argv of the command line because are used by ROS as remapping arguments
    //node_name in this case example1_a
    //optional options
    //this function do not contact the master
    ros::init(argc, argv, "example1_b");

    //To start the roscpp node the only thing to do is to create a ros::NodeHadle object.
    //This automatically call at the creation ros::start() and ros::shutdown() that can be also used to
    //control manually the creation a destruction of a node.
    //When ros::shutdown() is called, open subscriptions, publications, service calls and service servers 
    //will be destroied.
    ros::NodeHandle n;

    //This function is used to subscribe the node created previously.
    //Such a function accepts some parameters :
    //the topic to which subscribing to
    //the maximum size of the incoming messages to queue up for processing
    //the callback to call when the message has arrived
    ros::Subscriber sub = n.subscribe("message",1000, chatterCallback);
    
    //In this case ros::spin() is used, that means that all the callbacks will be called by ros::spin().
    //ros::spin() will not return until ros::shutdown() or Ctrl-C is pressed.
    ros::spin();
    
    return 0;
}