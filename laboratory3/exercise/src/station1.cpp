#include <ros/ros.h>
#include "exercise2/srv1.h"

int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "station");

    //Start the node
    ros::NodeHandle n;

    //Create client
    ros::ServiceClient client = n.serviceClient<exercise2::srv1>("robot_infos");
    
    //Random number for the frequency
    int frequency = std::rand() % 10 + 1;

    //Random number for charging station
    int chargingStation = std::rand() % 3 + 1;

    //Frequency loop rate
    ros::Rate loopRate(frequency);

    //sequence value
    int seq = 0;

    ROS_INFO("prova");

    while(ros::ok())
    {
        
        exercise2::srv1 srv;
        srv.request.stdMsgHeader.stamp = ros::Time::now();
        srv.request.stdMsgHeader.frame_id = "station" + chargingStation;
        srv.request.stdMsgHeader.seq = seq;
        seq++;

        //Call the server
        if (client.call(srv))
        {            
            //If the server responds, print the request and response
            ROS_INFO_STREAM("\n REQUEST : \n" << srv.request.stdMsgHeader << " " << srv.request.chargingStationID);
            ROS_INFO_STREAM("\n RESPONSE : \n" << srv.response.stdMsgHeader << " " << srv.response.messageContent);
        }
        else
        {
            //If the server does not response, print an error            
            ROS_ERROR("BATTERY DIED");
            return 1;
        }
        loopRate.sleep();
    }    
    return 0;
}