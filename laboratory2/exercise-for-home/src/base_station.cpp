#include <ros/ros.h>
#include "exercise/msg1.h"


void callback(const exercise::msg1::ConstPtr& infoRobot);

int main(int argc, char **argv)
{
    //Create Node
    ros::init(argc,argv, "base_station");

    //Start Node
    ros::NodeHandle node;

    //Create published
    ros::Subscriber subscriber = node.subscribe("infos",1000,callback);
    
    //5hz
    ros::Rate loop_rate(5);

    while(ros::ok())
    {
        //get the message published by robot
        ros::spin();

        //wait correct time
        loop_rate.sleep();
    }
    return 0;
}

void callback(const exercise::msg1::ConstPtr& infoRobot)
{    
    //for printing like c++ with streams
    ROS_INFO_STREAM( "roomId : " << infoRobot->roomId << " room : "<< infoRobot->roomName << " batteryPercentage " << infoRobot->batteryPercentage);
}