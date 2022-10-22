#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <intro_tutorial/FibonacciAction.h>

class FibonacciAction
{
protected:
    //Node for the server
    ros::NodeHandle nh_;

    //This must be created after the Node
    actionlib::SimpleActionServer<intro_tutorial::FibonacciAction> as_;

    //Name of the action
    std::string action_name_;
    
    //Feedback message to be published
    intro_tutorial::FibonacciFeedback feedback_;
    
    //Final result message to be published
    intro_tutorial::FibonacciResult result_;

public:
    FibonacciAction(std::string name) : 
        //Initialize the Action Server member of the class
        as_(nh_, //A node to create a namespace under
            name, //Name for the action server
            //Need to pass as a parameter the callback that will be executed by the server whenever
            //a new goal is received by the clients. This allows clients to have blocking callbacks            
            //Notice that it is executed on a different thread

            //boost::bind is a special function that allows to define a function that
            //have eventually as a parameter both the caller object and the parameter to pass to the 
            //function to which call on the object caller
            //In this case, the function to execute is FibonacciAction::executeCB, the object to call such
            //a function which is a member function is this, and the parameter to pass to that call is variable (_1)
            boost::bind(&FibonacciAction::executeCB, 
                        this, 
                        _1), 
            false), //not auto starting
        action_name_(name) //Initialize action name with the name provided from the constructor
    {
        as_.start(); //explicity start the server
    }


    ~FibonacciAction(void) {}
    void executeCB(const intro_tutorial::FibonacciGoalConstPtr &goal)
    {
        //1Hz rate
        ros::Rate r(1);
        
        bool success = true;

        //Clear the fibonacci sequence feedback message
        feedback_.sequence.clear();
        
        //push the 2 base cases on the fibonacci sequence feedback message
        feedback_.sequence.push_back(0);
        feedback_.sequence.push_back(1);

        //Repeat until the goal
        for (int i = 1; i <= goal->order; i++)
        {
            //if request are preemped or the node is shutted down
            if (as_.isPreemptRequested() || !ros::ok())
            {
                ROS_INFO("%s: Preempted", action_name_.c_str());
                //set status of active goal preempted
                as_.setPreempted();
                //exit
                success = false;
                break;
            }
            //Compute the fibonacci of [i] and push back to the feedback the result
            feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i - 1]);
            
            //public the feedback
            as_.publishFeedback(feedback_);
            
            //wait the correct amount of time to reach 1 sec
            r.sleep();
        }

        //if not a failure
        if (success)
        {
            //create result message
            result_.sequence = feedback_.sequence;
            
            ROS_INFO("%s: Succeeded", action_name_.c_str());

            //set the status to success
            as_.setSucceeded(result_);
        }
    }
};

int main(int argc, char **argv)
{    
    //Create a node
    ros::init(argc, argv, "fibonacci");

    //Create an object of class FibonacciAction
    FibonacciAction fibonacci("fibonacci");

    //Call all the callbacks
    ros::spin();
    return 0;
}