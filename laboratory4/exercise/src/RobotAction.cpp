#include <exercise3/RobotAction.h>

RobotAction::RobotAction(std::string name) : 
            actionServer(node,name,boost::bind(&RobotAction::callback, this, _1),false),
            actionName(name)
            
{
    actionServer.start();
    feedback.currentBatteryLevel = CURRENT_BATTERY_LEVEL;
    feedback.stdMessageHeader.stamp = ros::Time::now();
    feedback.stdMessageHeader.frame_id = "Charging ...";
}

void RobotAction::callback(const exercise3::BatteryGoalConstPtr &goal)
{    
    ROS_INFO_STREAM("Stamp : " << goal->stdMessageHeader.stamp << " Frame Id: " << goal->stdMessageHeader.frame_id 
                    << " Battery Level Goal: " << goal->goalBatteryLevel << std::endl);

    //1Hz rate
    ros::Rate r(1);
    
    //Increment to reach the exact value after
    float increment = (goal->goalBatteryLevel - CURRENT_BATTERY_LEVEL) / 60;

    //Errors variable
    bool success = true;

    for(int i = 0; i <= 60; i++)
    {
        if (actionServer.isPreemptRequested() || !ros::ok())
        {
            ROS_INFO("%s: Preempted", actionName.c_str());
            
            //set status of active goal preempted
            actionServer.setPreempted();
            
            //exit
            success = false;        
            break;
        }
        //public the feedback
        actionServer.publishFeedback(feedback);

        //Set Standard Header
        feedback.stdMessageHeader.stamp = ros::Time::now();
        feedback.stdMessageHeader.frame_id = "Charging ...";
        //Increment Battery Level
        feedback.currentBatteryLevel += increment;        

        //wait the correct amount of time to reach 1 sec
        r.sleep();
    }

    

    if (success)
    {
        //create result message
        result.completedCharge = true;
        result.stdMessageHeader.stamp = ros::Time::now();
        result.stdMessageHeader.frame_id = "Charging Completed!";
            
        ROS_INFO("%s: Succeeded", actionName.c_str());

        //set the status to success
        actionServer.setSucceeded(result);
    }
}