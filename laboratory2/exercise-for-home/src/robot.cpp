#include <ros/ros.h>
#include "exercise/msg1.h"

int main(int argc, char **argv)
{
    //Create Node
    ros::init(argc,argv, "robot");

    //Start Node
    ros::NodeHandle node;

    //Create published
    ros::Publisher publisher = node.advertise<exercise::msg1>("infos",1000);
    
    //5hz
    ros::Rate loop_rate(5);
    
    //message to send
    exercise::msg1 message;   
    message.batteryPercentage = 80.0;

    while(ros::ok())
    {
        //construct the message to publish 
        

        int random = std::rand() % 5 + 1;
        message.roomId = random;
        switch (random)
        {
            case 1:
                message.roomName = "Robot Vision Lab";
                break;
            case 2:
                message.roomName = "SSL Lab";
                break;
            case 3:
                message.roomName = "IAS-Lab";
                break;
            case 4:
                message.roomName = "Neurorobotics Lab";
                break;
            case 5:
                message.roomName = "Autonomous Robotics Lab";
                break;
        }
        message.batteryPercentage -= 2.0;

        if(message.batteryPercentage < 0)
        {
            ros::shutdown();
        }

        //Publish messages
        publisher.publish(message);

        //call the callbacks
        ros::spinOnce();

        //wait correct time
        loop_rate.sleep();
    }
    return 0;
}