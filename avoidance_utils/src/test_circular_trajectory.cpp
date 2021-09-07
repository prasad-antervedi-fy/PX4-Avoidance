//
// Created by intern on 9/1/21.
//

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
geometry_msgs::PoseStamped current_position;
const int RADIUS = 5;
const double MULT = 0.001;
void positionCallback(const geometry_msgs::PoseStampedConstPtr& msg){
    current_position = *msg;

}

void calculateSetpointCircularTrajectory(geometry_msgs::PoseStamped& pose){
   static int i = 0;
   double theta = MULT*i;
   std::cout<<theta<<std::endl;
   pose.header.frame_id = "local_origin";
   pose.header.stamp = ros::Time::now();
   pose.pose.position.x = RADIUS*cos(theta);
   pose.pose.position.y = RADIUS*sin(theta);
   pose.pose.position.z = 3;

   pose.pose.orientation.x = 0;
   pose.pose.orientation.y = 0;
   pose.pose.orientation.z = 0;
   pose.pose.orientation.w = 1;

    i++;
}
int main(int argc, char** argv){
    ros::init(argc, argv, "test_circular_trajectory");
    ros::NodeHandle nh;

    // Subscribe to the move_base/simple_goal for yaw and /local_planner_manager/setpoint_position/local for positon setpoints
    //ros::Subscriber sub_yaw = nh.subscribe("/move_base_simple/goal", 1000, yawCallback);
    ros::Subscriber sub_position = nh.subscribe("/mavros/local_position/pose", 1000, positionCallback);

    ros::Publisher pub_movebase_goal = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);
    ros::Rate rate(50);
    while(ros::ok()){
        geometry_msgs::PoseStamped goal_position;
        calculateSetpointCircularTrajectory(goal_position);
        pub_movebase_goal.publish(goal_position);
        rate.sleep();
        //ros::spinOnce();
    }
    return EXIT_SUCCESS;
}