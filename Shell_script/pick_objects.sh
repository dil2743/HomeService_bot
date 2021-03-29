#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 10
xterm -e " rosrun rviz rviz -d /home/workspace/catkin_ws/src/rviz_config.rviz" &
sleep 10
rosrun pick_objects pick_objects 
