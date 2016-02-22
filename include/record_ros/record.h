#ifndef RECORD_ROS_RECORD_H_
#define RECORD_ROS_RECORD_H_

#include "record_ros/String_cmd.h"
#include <boost/scoped_ptr.hpp>
#include <std_msgs/String.h>
#include <boost/thread.hpp>

#include <rosbag/recorder.h>
#include <rosbag/bag.h>

class Record : public rosbag::Recorder{

public:

    Record(ros::NodeHandle& nh,rosbag::RecorderOptions const& options);

   // ~Record();
     volatile bool b_record;

//    boost::scoped_ptr<rosbag::Recorder> recorder;
//hello travis
//agaom

private:

    bool string_command(record_ros::String_cmd::Request& req, record_ros::String_cmd::Response& res);

    void string_command2(const std_msgs::String::ConstPtr& msg);

private:

    ros::ServiceServer          service_srv;
    ros::Subscriber             topic_cmd;
 //   boost::thread thread;





};


#endif
