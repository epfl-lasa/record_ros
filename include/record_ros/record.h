#ifndef RECORD_ROS_RECORD_H_
#define RECORD_ROS_RECORD_H_

#include "record_ros/String_cmd.h"
#include <std_msgs/String.h>
#include <rosbag/recorder.h>

class Record : public rosbag::Recorder{

public:

    Record(ros::NodeHandle& nh,rosbag::RecorderOptions const& options);

    void wait_for_callback();

private:

    bool string_command(record_ros::String_cmd::Request& req, record_ros::String_cmd::Response& res);

private:

    bool                        b_record;
    ros::ServiceServer          service_srv;
    ros::Subscriber             topic_cmd;

};


#endif
