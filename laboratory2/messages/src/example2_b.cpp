#include "ros/ros.h"
#include "intro_tutorial/msg1.h"

//This is an example of a subscriber that receive a message from a pulisher
//Notice that the message in this case is a data structure that is composed of 3 integers declared inside
//msg folder and in particular in msg/msg1.msg (custom message)


//Callback that print the heard custom message
//Notice that, actually, the parameter passed is the message that must be printed
void messageCallback(const intro_tutorial::msg1::ConstPtr &msg)
{
    //Print the heard message
    ROS_INFO("I heard: [%d] [%d] [%d]", msg->A, msg->B, msg->C);
}

int main(int argc, char **argv)
{
    //Creation of the node
    ros::init(argc, argv, "example2_b");
    
    //Start the Node
    ros::NodeHandle n;
    
    //Subscription
    ros::Subscriber sub = n.subscribe("message",1000, messageCallback);
    
    //Execute all the callbacks
    ros::spin();
    return 0;
}