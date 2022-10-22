# ROS Tutorail

## ROS Nodes
ROS Nodes can be created by putting `.cpp` or `.py` code files inside `<path_package_name>/src`, in this case, inside `~/catkin_ws/src/intro_tutorial/src`.
After that, `<path_package_name>/CMakeLists.txt` file must be modified in order to compile correctly the code, in this case the file `~/catkin_ws/src/intro_tutorial/CMakeLists.txt`. The modifications to be done are the followings :
- in the section **Declare C++ executable** this piece of code must be placed :
    ```
    add_executable(<name_file> src/<name_file>.cpp)
    ```
- in the section **Specify libraries to link a library or executable target against** this piece of code must be placed :
    ```
    target_link_libraries(<name_file> ${catkin_LIBRARIES})
    ```
- Execute : `catkin_make` or `catkin build` (from `~/catkin_ws`).
- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
    - Press `CTRL` + `SHIFT` + `B`.
    - Run `catkin_make: build`.
- Run the code :
	- Open a terminal and execute : `roscore`. (To check if ROS is already running use the command `rosnode list`).
	- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
	    - Press `CTRL` + `SHIFT` + `P`.
	    - Select `ROS: Start`.
	- Open different shells for each node created and run :
	    ```
        rosrun <package_name> <name_file>
        ```
Other interesting commands regarding nodes are :	
- `rosnode info <node_name>` : printing information about a node.
- `rosnode kill <node_name>` : killing a running node.
- `rosnode list` : listing the active nodes.
- `rosnode ping <node_name>` : testing the connectivity to a node.
- `rostopic echo <msg_name>` : printing messages to the screen.
- `rostopic find <msg_type>` : finding topics by their type.
- `rostopic info <msg_name>` : printing the information about the active topic.
- `rostopic list` : printing information about acrive topics.
- `rostopic type <msg_name>` : printing the topic type.
