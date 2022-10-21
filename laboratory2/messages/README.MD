# ROS Tutorail

## ROS Messages
ROS messages can be created as follows :
- Create a folder `msg` inside the folder `<path_package_name>`.
- Create a `msg1.msg` file with the following content :
    ```
    int32 A
    int32 B 
    int32 C
    ```
- Edit `<path_package_name>/package.xml` by adding after the last `<export>...</export>` tag the following code :
    ```
    <build_depend>message_generation</build_depend>
    <exec_depend>message_runtime</exec_depend>
    ```
- Modify the file `<path_package_name>/CMakeLists.txt` as follow :
    - in the section **Find catkin macros and libraries** this piece of code must be placed : 
        ```
        find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)
        ```
    - in the section **catkin specific configuration** this piece of code must be placed : 
        ```
        catkin_package(CATKIN_DEPENDS message_runtime)
        ```
    - in the section **Generate messages in the 'msg' folder** this piece of code must be placed : 
        ```
        add_message_files(FILES msg1.msg)
        ```
    - in the section **Generate added messages and services with any dependencies listed here** this piece of code must be placed :
        ```
        generate_messages(DEPENDENCIES std_msgs)
        ```
- Execute : `catkin_make` or `catkin build` (from `~/catkin_ws`).
- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
    - Press `CTRL` + `SHIFT` + `B`.
    - Run `catkin_make: build`.
- To check that all is OK, the following command must be exectuted : `rosmsg show <package_name>/<msg_name>` in this case, `rosmsg show <package_name>/msg1`. 
If everything was done correctly, the following output will be displayed :
    ```
    int32 A
    int32 B 
    int32 C
    ```
Other interesting commands regarding messages are :
- `rosmsg list` : list all messages.
- `rosmsg <package_name>` : list all of the messages in a package.
- `rosmsg packages <msg_name>` : list all of the packages that have the <msg_name>.