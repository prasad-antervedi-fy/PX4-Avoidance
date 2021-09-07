#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>


geometry_msgs::PoseStamped target_yaw, target_position;
ros::Publisher pub_setpoint_position;
bool new_yaw = false, new_position = false;
void yawCallback(const geometry_msgs::PoseStampedConstPtr& msg){
   target_yaw = *msg;
   new_yaw = true;
}

void positionCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    target_position = *msg;
    target_position.pose.orientation.x = 0;
    target_position.pose.orientation.y = 0;
    target_position.pose.orientation.z = 0;
    target_position.pose.orientation.w = 1;
    target_position.header.stamp = ros::Time::now();
    pub_setpoint_position.publish(target_position);
    new_position = true;
}

void resetBools(){
    new_yaw = false;
    new_position = false;
}

void setTargetPose(geometry_msgs::PoseStamped& pose){
    pose.header.stamp = ros::Time::now();
    //REVIEW: Check back on this
    //pose.header.frame_id = "local_origin";
    pose.pose.orientation.w = target_yaw.pose.orientation.w;
    pose.pose.orientation.x = target_yaw.pose.orientation.x;
    pose.pose.orientation.y = target_yaw.pose.orientation.y;
    pose.pose.orientation.z = target_yaw.pose.orientation.z;

    pose.pose.position.x = target_position.pose.position.x;
    pose.pose.position.y = target_position.pose.position.y;
    pose.pose.position.z = target_position.pose.position.z;


}
int main(int argc, char **argv){
	ros::init(argc, argv, "avoidance_utils");
	ros::NodeHandle nh;

    // Subscribe to the move_base/simple_goal for yaw and /local_planner_manager/setpoint_position/local for positon setpoints
	//ros::Subscriber sub_yaw = nh.subscribe("/move_base_simple/goal", 1000, yawCallback);
    ros::Subscriber sub_position = nh.subscribe("/planner/setpoint_position/local", 1000, positionCallback);

    pub_setpoint_position = nh.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 1000);
    //ros::Rate rate(20);

    ros::spin();

    /*while(ros::ok()){

        if(new_position) {
            geometry_msgs::PoseStamped target_pose;
            setTargetPose(target_pose);
            pub_setpoint_position.publish(target_pose);
            std::cout<<"target pose published !!\n";
        }
        resetBools();
        ros::spinOnce();
        rate.sleep();
    }*/
	return 0;


}
