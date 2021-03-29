#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 10
RVIZ_CONFIG_FILE=$(readlink -f rviz_config.rviz)
xterm -e " rosrun rviz rviz -d $RVIZ_CONFIG_FILE "  &
sleep 10
rosrun using_markers add_marker 


