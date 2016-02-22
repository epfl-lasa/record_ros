#include "record_ros/record.h"
#include <ros/ros.h>
#include <boost/thread.hpp>

Record::Record(ros::NodeHandle &nh,rosbag::RecorderOptions const& options):
rosbag::Recorder(options)
{
    service_srv = nh.advertiseService("cmd",&Record::string_command,this);
    b_record    = false;

}

void Record::wait_for_callback(){
    ros::Rate r(10); // 10 hz
    while (!b_record)
    {
        ros::spinOnce();
        r.sleep();
    }
}

bool Record::string_command(record_ros::String_cmd::Request& req, record_ros::String_cmd::Response& res){
    std::string cmd = req.cmd;
    if(cmd == "record"){
       // thread = boost::thread(&rosbag::Recorder::run,recorder.get());
        b_record = true;
       // thread.detach();
        res.res     = "starting recorder";
        return true;
    }else if(cmd == "stop"){
        ros::shutdown();
    //    thread.join();
        res.res = "stopping recorder";
        return true;
    }else{
        res.res = "No such command[" + cmd + "] in [Record::string_command]";
        ROS_WARN_STREAM(res.res);
        return false;
    }
}
