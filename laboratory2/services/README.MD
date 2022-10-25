# ROS Tutorail

# ROS Services
ROS services can be created as follows :
- Create a folder `srv` inside the folder `<path_package_name>`.
- Create a `srv1.srv` file with the following content :
    ```
    int32 A
    int32 B 
    int32 C
    ---
    int32 sum
    ```
- Modify the file `<path_package_name>/CMakeLists.txt` as follow :
    - in the section **Find catkin macros and libraries** this piece of code must be placed : 
        ```
        find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)
        ```
    - in the section **Generate added messages and services with any dependencies listested here** this piece of code must be placed : 
        ```
        generate_messages(DEPENDENCIES std_msgs)
        ```
    - in the section **Specify additional locations of header files** this piece of code must be placed : 
        ```
        include_directories(include ${catkin_INCLUDE_DIRS})
        ```
    - in the section **Generate services in the 'srv' folder** this piece of code must be placed :
        ```
        add_service_files(FILES <name_service>.srv)
        ```
- Execute : `catkin_make` or `catkin build` (from `~/catkin_ws`).
- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
    - Press `CTRL` + `SHIFT` + `B`.
    - Run `catkin_make: build`.
- To check that all is OK, the following command must be exectuted : `rossrv show <package_name>/<srv_name>` in this case, `rossrv show <package_name>/srv1`. 
If everything was done correctly, the following output will be displayed :
    ```
    int32 A
    int32 B 
    int32 C
    ---
    int32 sum
    ```
Other interesting commands regarding services are :
- `rosservice call <srv_name> [args]` : calling the service with the arguments provided.
- `rosservice find [srv_type]` : finding services by service type.
- `rosservice info <srv_name>` : printing information about the service.
- `rosservice list` : listing the active services.
- `rosservice type <srv_name>` : printing the service type.
