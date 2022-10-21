#include "ros/ros.h"
#include "intro_tutorial/srv1.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "add_3_ints_client");
    
    //This node requires as argument when started 3 paramters (actually 4)
    //Therefore if less, then returns an error and log a message
    if (argc != 4)
    {
        ROS_INFO("usage: add_3_ints_client A B C ");
        return 1;
    }

    //Start the node
    ros::NodeHandle n;

    //Call serviceClient to connect to the the server, notice that it is specified that
    //it will be send as a mesage a srv1 which actually is a service.
    ros::ServiceClient client = n.serviceClient<intro_tutorial::srv1>("add_3_ints");
    
    //Create the service message with data read from command line to send to the server
    intro_tutorial::srv1 srv;
    srv.request.A = atoll(argv[1]);
    srv.request.B = atoll(argv[2]);
    srv.request.C = atoll(argv[3]);

    //Call the server
    if (client.call(srv))
    {
        //If the server responds, print the response
        ROS_INFO("Sum: %ld", (long int)srv.response.sum);
    }
    else
    {
        //If the server does not response, print an error
        ROS_ERROR("Failed to call service add_3_ints");
        return 1;
    }
    return 0;
}