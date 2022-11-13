#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <exercise3/BatteryAction.h>
#include <exercise3/RobotAction.h>

int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "robot");

    ROS_INFO_STREAM("STARTED SERVER" << std::endl);

    //Create an object of class RobotAction
    RobotAction robot("battery");

    //Call all the callbacks
    ros::spin();
    
    return 0;
}
