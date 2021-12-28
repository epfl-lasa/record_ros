#include "record_ros/record.h"
#include <ros/ros.h>
#include <boost/thread.hpp>



static void cb_shutdown(const ros::TimerEvent&){
  ros::shutdown();
}

Record::Record(ros::NodeHandle &nh,rosbag::RecorderOptions const& options):
    rosbag::Recorder(options)
{
    service_srv = nh.advertiseService("cmd",&Record::string_command,this);
    b_record    = false;
    shutdown_timer = nh.createTimer(ros::Duration(0.1), cb_shutdown,true,false);
}


void Record::wait_for_callback(){
    ros::Rate r(100); // 60 hz
    while (!b_record && ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
}

bool Record::string_command(record_ros::String_cmd::Request& req, record_ros::String_cmd::Response& res){
    std::string cmd = req.cmd;
    ROS_INFO("Record callback");
    if(cmd == "record"){
        if(b_record){
            shutdown_timer.start();
            res.res = "stopping recorder";
        }else{
            b_record = true;
            res.res  = "starting recorder";
        }
        return true;
    }else if(cmd == "stop"){
        shutdown_timer.start();
        res.res = "stopping recorder";
        return true;
    }else{
        res.res = "No such command[" + cmd + "] in [Record::string_command]";
        ROS_WARN_STREAM(res.res);
        return false;
    }
}
