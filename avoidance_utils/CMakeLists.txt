cmake_minimum_required(VERSION 3.0.2)
project(avoidance_utils)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES avoidance_utils
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(avoidance_topic_util src/avoidance_topic_util.cpp)
add_executable(test_circular_trajectory src/test_circular_trajectory.cpp)

target_link_libraries(avoidance_topic_util ${catkin_LIBRARIES})
target_link_libraries(test_circular_trajectory ${catkin_LIBRARIES})
