#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <intro_tutorial/FibonacciAction.h>


int main(int argc, char **argv)
{
    //Create a node
    ros::init(argc, argv, "test_fibonacci");

    //Create the action client
    actionlib::SimpleActionClient<intro_tutorial::FibonacciAction> ac("fibonacci", true);


    ROS_INFO("Waiting for action server to start.");
    
    //Wait that the action server connects to this client
    //Notice that this must be used in a separate thread due to the fact that otherwise the client 
    //will never start. This consists of negotiationg the connection between client and sever
    ac.waitForServer(); // will wait for infinite time


    ROS_INFO("Action server started, sending goal.");

    //Create a message goal that must be sended to the server
    intro_tutorial::FibonacciGoal goal;
    goal.order = 20;

    //Send the goal to the server and also register the callbacks
    //If a previous goal was already active when this is called, that previous goal will be forgotten
    //and, the new goal will start
    ac.sendGoal(goal);

    //Wait until the goal has not finished or in this case, wait at most 30 seconds
    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

    //if finished
    if (finished_before_timeout)
    {
        //Get the information for this goal (PENDING,ACTIVE,REJECTED,PREEMPTED,ABORTED,SUCCEDED,LOST)
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s", state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out.");
    return 0;
}