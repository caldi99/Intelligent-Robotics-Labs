# ROS Tutorial

# Launch Files
A `.launch` file is a file that can be used to launch more than one one. To create a `.launch` file the following steps must be done :
- Move in the package for which creating a `.launch` file : `roscd <package_name>`.
- Create a folder called launch : `mkdir launch`.
- Move inside the folder launch : `cd launch`.
- Create an `<name_launch_file.launch>` and copy the following code by adpting it to your situation :
    ```
    <?xml version="1.0"?>
    <launch>
        <node name ="<node_name_symbolic>" pkg="<package_name>" type="<name_node_file_cmakelists>" />
    </launch>
    ```
- Launch the file : `roslaunch <package_name> <name_launch_file>.launch`
- To check if everything has worked correctly the following commands can be applied :
    - `rosnode list` : list the active nodes.
    - `rqt_console` : show the running nodes.
    - `rosrun rqt_graph rqt_graph` : show the running nodes graphically.
