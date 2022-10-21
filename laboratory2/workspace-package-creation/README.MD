# ROS Tutorail

## Creating a ROS Workspace
To create a **ROS Workspace** steps must be done : 
- Create a folderfor the workspace : `mkdir ~/name_of_the_folder/src` for instance : `md ~/catkin_ws/src`.
- Move inside `~/catkin_ws/src` : `cd ~/catkin_ws/src`.
- Execute the following command : `catkin_init_workspace`. 
Such command will initialize the `~/catkin_ws/src` workspace. 
- Move inside `~/catkin_ws/` : `cd ~/catkin_ws/`.
- Execute `catkin build` or `catkin_make`.
Both of those two commands are used to build any packages located in `~/catkin_ws/src` and  **must always be executed** from the folder `~/catkin_ws` if the objective is to build all the packages created.
- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
    - Press `CTRL` + `SHIFT` + `B`.
    - Run `catkin_make: build`.
- (Only this time) execute : `echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc`. 
This command is used to write `source ~/catkin_ws/devel/setup.bash` in the file `~/.bashrc` in order to avoid to execute the next command every time.
- (Only this time) execute : `source ~/catkin_ws/devel/setup.bash`.
This command is used to set Enviromental Variables.

Other commands worth to mention are :
- `catkin build <target_package>` : to build a specific package.
- `catkin build --this` : to build the package contained in the current working directory.

## Creating a ROS package

In order to create a package in ROS the following steps must be followed :
- Move inside `~/catkin_ws/src` (where the workspace was created) : `cd ~/catkin_ws/src`
- Execute the following command : `catkin_create_pkg <package_name> [depend1] [depend2] [depend3]` where `<package_name>` is the name of the package that must be created and `[depend1] [depend2] [depend2]` are optional dependancies like `std_msg`, `rospy`, `roscpp`. 
As an example the command used to create a package in this tutorial is : `catkin_create_pkg intro_tutorial std_msgs roscpp`
- Build the package created with either :
    - `cd ~/catkin_ws`.
    - `catkin_make` or `catkin build`.
- (Optional) If the **ROS extension** of Visual Studio Code is installed, the previous step can be substituted with :
    - Press `CTRL` + `SHIFT` + `B`.
    - Run `catkin_make: build`.

Notice that, after creating a package some commands can be used like :
- `rospack find <package_name>` : to know the path of where it is located **package_name**.
- `rosstack find <metapackage_name>` : to retrieve information about ROS stacks for **metapackage_name**.
- `rosls <package_name>` : to list the content of **package_name**.
- `roscd <package_name>` : to move in where it is located **package_name**.
- `rosed <package_name> <file_name>` : to modify a file with the integrated **vim** in ROS.