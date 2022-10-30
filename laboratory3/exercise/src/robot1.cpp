#include <ros/ros.h>
#include "exercise2/srv1.h"
#include "exercise2/msg1.h"

float batteryPercentage = 100.0;

bool callbackRobotResponse(exercise2::srv1::Request &req, exercise2::srv1::Response &res)
{
    if(batteryPercentage < 0)
    {
        ros::shutdown();
    }

    int random = std::rand() % 5 + 1;

    //message : <roomId,roomName,batteryPercentage>
    res.messageContent.roomId = random;
    switch (random)
    {
        case 1:
            res.messageContent.roomName = "Robot Vision Lab";
            break;
        case 2:
            res.messageContent.roomName = "SSL Lab";
            break;
        case 3:
            res.messageContent.roomName = "IAS-Lab";
            break;
        case 4:
            res.messageContent.roomName = "Neurorobotics Lab";
            break;
        case 5:
            res.messageContent.roomName = "Autonomous Robotics Lab";
            break;
    }

    res.messageContent.batteryPercentage = batteryPercentage;
    batteryPercentage -= 2.0;

    res.stdMsgHeader.stamp = ros::Time::now();
    if(batteryPercentage > 0)
    {
        res.stdMsgHeader.frame_id = "navigation";
    }else
    {
        res.stdMsgHeader.frame_id = "stopped";
    }
    res.stdMsgHeader.seq = req.stdMsgHeader.seq;
    
    return true;
}

int main(int argc, char **argv)
{
    // Create a node
    ros::init(argc, argv, "robot");

    // Start a node
    ros::NodeHandle node;

    // Create the server
    ros::ServiceServer server = node.advertiseService("robot_infos", callbackRobotResponse);

    // Call all the callbacks and block the process   
    ros::spin();

    return 0;
}