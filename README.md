# record_ros
[![Build Status](https://travis-ci.org/epfl-lasa/record_ros.svg?branch=master)](https://travis-ci.org/epfl-lasa/record_ros/branches)

A callback wrapper for rosbag record, where a ros service allows a user to start recording a set of topics and 
also stop.

# Launch file

Three arguments have to be over-written in your own launch file;

* **path_save**: system dependent path to folder where all the rosbags will be put: /home/user/rosbag_record 
* **topic**: set of space sperated topics: topic1 topic2 topic3 ...
* **file_name**: the name prefix which will be put before the rosbag time stamp (optional)

# Quick example

TODO
