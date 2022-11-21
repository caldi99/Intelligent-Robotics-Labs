# CMakeLists.txt file Analysis for a ROS Package

A **CMakeLists.txt** file that is created inside a ROS package is divided into some importat parts :
- First part : this part is composed by mainly two important blocks :
    - the spcification of the **CMake** to use and, the specification of the **package name** with respectively, `cmake_minimum_required` and `project`.
    - the second part, is defined by `find_package` where there are listed all the **external packages** used by the current package. 
    Such packages are :
        - the ones specified during the **creation** of the package with the command : `catkin_create_pkg <package_name> [package_1] [package_2] .. [package_i]`
        - packages **not** specified during the **creation** of the package, and those can be :
            - packages installed with **ROS** .
            - packages downloaded from the **web** (github).
        
            The last ones must be downloaded under the `<path_to_workspace>/workspace_name/src/` folder and built before using them.
    ```CMake
    cmake_minimum_required(VERSION <version_cmake>)
    project(<package_name>)

    find_package(catkin REQUIRED COMPONENTS
        <package_1>
        <package_2>
        ...
        <package_k>
    )   
    ```
    Notice that, when an **external package** is specified in the `CMakeLists.txt` with `find_package` automatically, or **manually** two entries (`<build_depend>package_i</build_depend>` and `<exec_depend>package_i</exec_depend>`), for each **<package_i>** must be /are **added** to the `package.xml`, created inside the folder of the package you are working i.e. `<package_name>/package.xml` when the package is created for the first time.
    ```xml
    <?xml version="1.0"?>
    <package format="2">
    <name>[package_name]</name>
    <version>0.0.0</version>
    <description>The [package_name] package</description>
    
    <maintainer email="username@todo.todo">username</maintainer>

    <license>TODO</license>

    <build_depend>package_1</build_depend>
    <exec_depend>package_1</exec_depend>

    <export>
    </export>
    </package>
    ```
- Second part : is used to specify the **messages**, **services** and **actions** defined inside the package. In particular, in a ROS package those 3 elements must be placed inside the directories `<path_to_package_name>/msg/` , `<path_to_package_name>/srv/` and `<path_to_package_name>/action/` respectively.
    ```CMake
    add_message_files(FILES 
        <message_name.msg> 
    )

    add_service_files(
        FILES
        <service_name.srv> 
    )

    add_action_files(
        FILES
        <action_name.action>
    )
    ```
- Third part : is used to specify the **C++** to compile and how to manage them. In particular inside this part, there are 2 main subparts :
    - first : is used to specify if the `<path_to_package_name>/include/` directory must be included, by uncommenting `include` in the `include_directories` and, `add_library` to specify the `.cpp` files that represent a library implemented by our own that does **not contain** the **main** function.
    - second : is used to specify the .cpp files that contains the main function. Notice that, if such files uses the library create by your own, then we must add inside `target_link_libraries` the name of the library i.e. `target_link_libraries(<executable_name> ... <library_name>)`.
    ```CMake
    include_directories(
    # include
    ${catkin_INCLUDE_DIRS}
    )
    add_library(
        <library_name> <path_to_file>/<library_name.cpp>
    )


    add_executable(<executable_name> src/<file_name>.cpp)
    add_dependencies(<executable_name> ${catkin_EXPORTED_TARGETS})
    target_link_libraries(<executable_name> ${catkin_LIBRARIES})
    ```