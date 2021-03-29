#!/bin/sh
xterm -e  " roscore " &
RVIZ_CONFIG_FILE=$(readlink -f rviz_config.rviz)
echo $RVIZ_CONFIG_FILE
xterm -e " rosrun rviz rviz -d $RVIZ_CONFIG_FILE " &
