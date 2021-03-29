#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/String.h"

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
 ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
/*
*set pick up location and wait till robot is bot is reached
*/

visualization_msgs::Marker marker;
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
  ROS_INFO("Pickup  point ");
   marker_pub.publish(marker);
   ros::Duration(5,0).sleep();
  ROS_INFO("Hiding Marker from pick point ");
   marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
   ros::Duration(5,0).sleep();
  ROS_INFO("Marker at DROPPING  point ");
  marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 3;
    marker.pose.position.y = 0;
  marker_pub.publish(marker);
   ros::Duration(5,0).sleep();
}
