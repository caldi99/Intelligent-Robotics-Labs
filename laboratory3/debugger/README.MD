# ROS Tutorail
## Debugging with VSCode
Before explaining how to debug code written in C++, for a ROS application, make sure that :
- **Visual Studio Code** is installed on your machine.
- **ROS Extension**, for Visual Studio Code, is installed.
- gdb is installed on your machine.

If those **requirements** are **satisfied** then, to debug a ROS Application the following steps must be followed:
- Create a `launch` directory inside the **package** where the files to debug are contained : 
    - `roscd <package_name>` or `cd <path_package>` 
    - `mkdir launch`
- Create a `.launch` file inside of the just created `launch` directory and modify the following piece of code by adding the corresponding correct values :
    ```    
    <?xml version="1.0"?>
    <launch>
        <node name ="<node_name_symbolic>" pkg="<package_name>" type="<name_node_file_cmakelists>" />
    </launch>
    ```
- Open the VSCode palette `CTRL` + `SHIFT` + `P` and select **ROS: Start**.
- Open the VSCode palette `CTRL` + `SHIFT` + `P` and selct **ROS: Update C++ Proprieties**.
- Close all **opened C++ files**.
- Click on the **Debug Tab** of Visual Studio Code.
- Click on **create a launch.json file**.
- Select **ROS**.
- Sekect **ROS Launch**.
- Select the **package** that contains the **files to debug**.
- Select the `.launch` file previously created.

This operation will create a `launch.json` file under the `.vscode` folder with the correct parameters to debug the ROS package. For instance the following piece of code should be seen inside the lanch.json file just mentioned
```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "ROS: Launch",
            "request": "launch",
            "target": "<path_package>/launch/<name_launch_file>.launch",
            "launch": [
                "rviz",
                "gz",
                "gzclient",
                "gzserver"
            ],
            "type": "ros"
        }
    ]
}
```
Notice that, if multiple `.launch` files are present, then just modify the `launch.json` file as follow :
```
...
    "configurations": [
        ...
        {
            "name": "ROS: Launch",
            "request": "launch",
            "target": "<path_package>/launch/<name_launch_file_i>.launch",
            "launch": [
                "rviz",
                "gz",
                "gzclient",
                "gzserver"
            ],
            "type": "ros"
        }, 
...
```

Finally, to **debug** the code : 
- Open a `.cpp` file to debug and place a **brakepoint**.
- Open the **Debug Tab** of Visual Studio Code and press `F5` or the **play button** on the **top-left corner**.
- Eventually, select the **Node to debug** if multiple nodes are launched with the .launch file