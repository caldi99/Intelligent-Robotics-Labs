#include "ros/ros.h"
#include "intro_tutorial/srv1.h"

//This is an example of a service. Service are a special kind of mesages that differ from "normal"
//messages that uses ROS Topics because they contain a request and a response.
//roscpp converts srv files into 3 classes that you need to be familiar with : service definition, request 
//messages and response messages. For instance :
//my_package/srv/Foo.srv ->
//  my_package::Foo
//  my_package::Foo::Request
//  my_package::Foo::Response

//Callback function that sums up the value written in the request, saves the result in the response
//and logs everything
bool add(intro_tutorial::srv1::Request &req, intro_tutorial::srv1::Response &res)
{
    res.sum = req.A + req.B + req.C;
    ROS_INFO("request: A=%d, B=%d C=%d", (int)req.A, (int)req.B, (int)req.C);
    ROS_INFO("sending back response: [%ld]", (int)res.sum);
    return true;
}
int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "add_3_ints_server");
    
    //Start the node
    ros::NodeHandle n;

    //Create a ServiceServer, with advertiseService() method of ros::NodeHanlde object.
    //Such a method requires the name of the service and a callbackfunction that will be called.
    //The behaviour of advertiseService() is pretty similar to subscribe()
    ros::ServiceServer service = n.advertiseService("add_3_ints", add);

    //Log a message
    ROS_INFO("Ready to add 3 ints.");

    //Call all the callbacks
    ros::spin();
    return 0;
}