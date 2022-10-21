#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

//This is an example on how to create a publisher node.
int main(int argc, char **argv)
{
    //To create a node you need to use ros::init where the parameters to be passed are :
    //argc and argv of the command line because are used by ROS as remapping arguments
    //node_name in this case example1_a
    //optional options
    //this function do not contact the master
    ros::init(argc, argv, "example1_a");

    //To start the roscpp node the only thing to do is to create a ros::NodeHadle object.
    //This automatically call at the creation ros::start() and ros::shutdown() that can be also used to
    //control manually the creation a destruction of a node.
    //When ros::shutdown() is called, open subscriptions, publications, service calls and service servers 
    //will be destroied.
    ros::NodeHandle n;

    //To create a node that publish messages to a topic we must call the advertize method on the node previously create
    //The parameters of this function are : the topic to advertize and the queue maximum size of outgoing messages 
    //for delivering to subscribers.
    //The object return is a ros::Publisher
    //Notice that when ros::shutdown is called ros::Publisher::shutdown is called as well.
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("message", 1000);

    //To publish messages with a certain amount of rate we use ros::Rate
    //This object receive as input the rate in Hz of the total time that the node must slepp after
    //calling on this object .sleep() method
    //Notice that, the amount of time waited by .sleep() is dynamic, i.e if we want execute a certain thing
    //with a node every 0.1s (10Hz) then, if doing the operation that we need to do takes only 0.02s on 
    //average then, sleep() will wait the necessary amount of time to meet that 0.1s.
    ros::Rate loop_rate(10);
        
    //ros::ok() check if the node is shutted down or not, (true not shutted down)
    while (ros::ok())
    {
        //Create a String Message to send to the subscribers
        std_msgs::String msg;
        std::stringstream ss;
        ss << " Hello World! ";
        msg.data = ss.str();
        
        //Logs the message sent to subscribers
        ROS_INFO("%s", msg.data.c_str());

        //Publish a message on the topic associated with this publisher.
        //This function is asynchronous and does the work only if there are subscribers connected to that topic
        chatter_pub.publish(msg);

        //Because callbacks subscriber's callbacks by default are not executed we need to explicitly 
        //say that we want to execute them. In particular ros::spinOnce() execute all the callbacks
        //that have waited to be called up to that point in time.
        ros::spinOnce();

        //Wait te necessary seconds
        loop_rate.sleep();
    }
    return 0;
}