#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"
#include <stdbool.h>
visualization_msgs::Marker marker;
ros::Publisher marker_pub;
int ROBOT_FSM = -1 ;

#define  Invalid_state   0
#define  Starting_motion  1
#define  Moving_toward_pickup_point  2
#define  Pickup_point_reached  3
#define  Moving_toward_dropping_point  4
#define  Dropping_point_reached  5

/*
* Callback function for odom topic 
*/
void odomCallback(const std_msgs::String::ConstPtr& msg)
{
   if(msg->data == "state_0"){
	ROS_INFO("About to start motion ");
     ROBOT_FSM = Starting_motion;
     marker.pose.position.x = 3;
     marker.pose.position.y = 3;
     ROS_INFO("Marker location set at (3,3)");
  }
  else if(msg->data == "state_1"){
	ROS_INFO("Moving towards pickup point ");
    ROBOT_FSM = Moving_toward_pickup_point;
     marker_pub.publish(marker);
  }
  else if(msg->data == "state_2"){
	ROS_INFO("Reached at pickup point ");
    ROBOT_FSM = Pickup_point_reached;
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
  }
  else if(msg->data == "state_3"){
	ROS_INFO("Moving towards droping point ");
    ROBOT_FSM = Moving_toward_dropping_point;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 3;
    marker.pose.position.y = 0;
    marker.color.b = 1.0f;
    marker.color.g = 0.0f;
    ROS_INFO("Marker set to be displayed at (3,-3)");
  }
  else if(msg->data == "state_4"){
	ROS_INFO("Reached at DROPPING  point ");
    ROBOT_FSM = Dropping_point_reached;
    marker_pub.publish(marker);
  }
 
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
   marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber sub_odom = n.subscribe("robot_status", 1000, odomCallback);  

/*
*set pick up location and wait till robot is bot is reached
*/
  uint32_t shape = visualization_msgs::Marker::CUBE;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();
	marker.ns = "basic_shapes";
	marker.id = 0;
	marker.type = shape;
	marker.action = visualization_msgs::Marker::ADD;
 	marker.pose.position.x = 3;
    marker.pose.position.y = 3;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

  ros::spin();
}
