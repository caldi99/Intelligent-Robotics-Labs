
# In order to make a script executable on Linux, use the “chmod” command and assign “execute” permissions to the file.
# You can either use the binary or the symbolic notation in order to make it executable.
# To use it give the following permissions
# $ chmod u+x script.sh
# $ chmod 744 script.sh

#!/bin/bash
if test -z "$1" ; then
    echo "YOU MUST SPECIFY A PARAMETER"
else 
    case $1 in

    build)
        #2 parameter : current working directory base name folder
        echo "building .." 
        eval "catkin config --extend /opt/ros/melodic"       
        eval "catkin build -w ~/$2/"
        ;;
    clear)
        echo "clearing .."
        eval "catkin clean --yes"
        ;;
    catkin_init_workspace)
        echo "create workspace .."
        eval "mkdir -p src"
        eval "source /opt/ros/melodic/setup.bash"
        eval "cd src"        
        eval "catkin_init_workspace"
        ;;
    create_package)
        #2 parameter : current working directory base name folder
        #3 parameter : name of the package
        echo "create package .."        
        eval "cd ~/$2/src/"
        eval "catkin_create_pkg $3 roscpp std_msgs --rosdistro melodic"
        ;;
    rostopic_info)   
        #2 parameter : current working directory base name folder
        eval "source ~/$2/devel/setup.sh"             
        eval "rostopic info $3"
        ;;
    rostopic_list)   
        #2 parameter : current working directory base name folder
        eval "source ~/$2/devel/setup.sh"     
        eval "rostopic list"
        ;;
    rosmsg_info)  
        #2 parameter : current working directory base name folder
        eval "source ~/$2/devel/setup.sh"      
        eval "rosmsg info $3"
        ;;
    rosmsg_list) 
        #2 parameter : current working directory base name folder
        eval "source ~/$2/devel/setup.sh"       
        eval "rosmsg list"
        ;;
    *)
        echo "TASK NOT FOUND"
        ;;
    esac
fi


