#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <exercise3/BatteryAction.h>


typedef actionlib::SimpleActionClient<exercise3::BatteryAction> Client;

// Called once when the goal completes
void doneCallback(const actionlib::SimpleClientGoalState& state,  const exercise3::BatteryResultConstPtr& result)
{
    ROS_INFO_STREAM("Finished in state" << state.toString().c_str() << std::endl);
    ROS_INFO_STREAM("Result " << std::endl);
    ROS_INFO_STREAM("Stamp : " << result->stdMessageHeader.stamp << " Frame Id: " << result->stdMessageHeader.frame_id 
                    << " Completed Charge: " << result->completedCharge << std::endl);
    
    ros::shutdown();
}

// Called once when the goal becomes active
void activeCallback()
{
  ROS_INFO_STREAM("ACTIVATED" << std::endl);
}

// Called every time feedback is received for the goal
void feedbackCallback(const exercise3::BatteryFeedbackConstPtr& feedback)
{
    ROS_INFO_STREAM("Stamp : " << feedback->stdMessageHeader.stamp << " Frame Id: " << feedback->stdMessageHeader.frame_id 
                    << " Battery Level: " << feedback->currentBatteryLevel << std::endl);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "station");

    //Create the action client
    Client actionClient("battery", true);

    // Wait the server
    actionClient.waitForServer();
    
    // Create Goal
    exercise3::BatteryGoal goal;
    goal.goalBatteryLevel = 80.0;
    goal.stdMessageHeader.stamp = ros::Time::now();
    goal.stdMessageHeader.frame_id = "Charge";
    
    //Send Goal
    actionClient.sendGoal(goal, &doneCallback, &activeCallback, &feedbackCallback);

    bool finishedBeforeTimeout = actionClient.waitForResult();

    //if finished
    if (finishedBeforeTimeout)
    {
        //Get the information for this goal (PENDING,ACTIVE,REJECTED,PREEMPTED,ABORTED,SUCCEDED,LOST)
        actionlib::SimpleClientGoalState state = actionClient.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out.");
    return 0;
}