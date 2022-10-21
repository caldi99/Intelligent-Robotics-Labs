#include "ros/ros.h"
#include "intro_tutorial/msg1.h"
#include <sstream>

//This is an example of a publisher that publish a message already
int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "example2_a");
    
    //Start the created node
    ros::NodeHandle n;

    //Create a publisher
    ros::Publisher pub = n.advertise<intro_tutorial::msg1>("message", 1000);
    
    //Publish with a frequency of 10Hz
    ros::Rate loop_rate(10);

    //Until the node is not shutted down
    while (ros::ok())
    {
        //Create a custom message to send
        intro_tutorial::msg1 msg;
        msg.A = 1;
        msg.B = 2;
        msg.C = 3;

        //Publish the custom message
        pub.publish(msg);

        //Explicitly state that callback's of the subscribers must be executed
        ros::spinOnce();

        //Wait the necessary remaining seconds
        loop_rate.sleep();
    }
    return 0;
}