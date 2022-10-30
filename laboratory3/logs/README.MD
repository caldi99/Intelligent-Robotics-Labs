# ROS Tutorail
## ROS Logs Output
One of the key features of ROS is that it allows developers to **log messages** with different levels of severity. However, the most important thing to know is **how to see those logs**. Normally, logs can be seen on a **terminal** from which a node has been executed but, this is **not the only way** and **neither** it is **always the correct one**. 
In particular we can say the following things :
-  If a node is executed with the command : `rosrun <package_name> <name_file>` then, logs will be visibile **only in the terminal** because the output will be redirected to **stdout** or **stderr** depending on the severity levels.
- If a node is executed through the `roslaunch <package_name> <name_file>` command, then logs will be visbile as **files** inside the folder `~/.ros/logs/`.
- In both cases logs can be seen with the command `rqt_console` which opens a graphical interface to show logs.

Other interesting commands are :
- `rosclean check` : **checks** how much **space** the current logs occupies in the `~/.ros/logs/` folder.
- `rosclean purge` : **remove** the content of the `~/.ros/logs/` folder.