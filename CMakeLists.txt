# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(write_publish)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
catkin_python_setup()

## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and doorIdentifier
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(doorIdentifier src/doorIdentifier.cpp)
target_link_libraries(doorIdentifier ${catkin_LIBRARIES})
add_dependencies(doorIdentifier beginner_tutorials_generate_messages_cpp)

catkin_install_python(PROGRAMS scripts/pyTalker.py scripts/pyListener.py scripts/action.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# %EndTag(FULLTEXT)%