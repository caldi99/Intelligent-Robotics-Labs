# ROS Tutorail
## ROS Action Messages
ROS action messages can be created as follows :
- Create a folder `action` inside the folder `<path_package_name>`.
- Create a `fibonacci.action` file with the following content :
    ```
    #goal definition
    int32 order
    ---
    #result definition
    int32[] sequence
    ---
    #feedback
    int32[] sequence
    ```
    As, shown, action messages requires to define a goal, result and feedback.
- Edit `<path_package_name>/package.xml` by adding after the last `<export>...</export>` tag the following code :
    ```
    <build_depend>actionlib</build_depend>
    <exec_depend>actionlib</exec_depend>
    ```
- Modify the file `<path_package_name>/CMakeLists.txt` as follow :
    - in the section **Find catkin macros and libraries** this piece of code must be placed : 
        ```
        find_package(catkin REQUIRED COMPONENTS actionlib)
        ```
    - in the section **Generate actions in the 'action' folder** this piece of code must be placed :
        ```
        add_action_files(DIRECTORY action FILES <action_name>.action)
        ```
    - in the section **Generate added messages and services with any dependencies listed here** this piece of code must be placed :    
        ```
        generate_messages(DEPENDENCIES actionlib_msgs)
        ```
    - in the section **Catkin specific configuration** this piece of code must be placed : 
        ```
        catkin_package(CATKIN_DEPENDS actionlib)
        ```

Notice that, in order to be able to execute code that uses actionlib, other than using as for the other examples :
- in the section **Declare C++ executable** this piece of code :
    ```
    add_executable(<name_file> src/<name_file>.cpp)
    ```
- in the section **Specify libraries to link a library or executable target against** this piece of code  :
    ```
    target_link_libraries(<name_file> ${catkin_LIBRARIES})
    ```

In addition to that, also, must be added :
- in the section **Add cmake target dependencies of the executable**
    ```
    add_dependencies(<name_file> ${<name_package>_EXPORTED_TARGETS})
    ```