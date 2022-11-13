#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <exercise3/BatteryAction.h>

class RobotAction
{
protected:
    //Node for the server
    ros::NodeHandle node;

    //This must be created after the Node
    actionlib::SimpleActionServer<exercise3::BatteryAction> actionServer;

    //Name of the action
    std::string actionName;
    
    //Feedback message to be published
    exercise3::BatteryFeedback feedback;
    
    //Final result message to be published
    exercise3::BatteryResult result;

    //Current Battery Level
    float CURRENT_BATTERY_LEVEL = 5.0;

public:
    RobotAction(std::string name);
    ~RobotAction() {}
    void callback(const exercise3::BatteryGoalConstPtr &goal);
};
#endif // ROBOTACTION_H
