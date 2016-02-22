#include "record_ros/record.h"
#include <ros/ros.h>
#include <boost/thread.hpp>

Record::Record(ros::NodeHandle &nh,rosbag::RecorderOptions const& options):
rosbag::Recorder(options)
{
    service_srv = nh.advertiseService("cmd",&Record::string_command,this);
    topic_cmd   = nh.subscribe("cmd",1,&Record::string_command2,this);
    b_record    = false;

}

/*
void Record::init(rosbag::RecorderOptions options){
    recorder.reset( new rosbag::Recorder(options) );
}
*//*
std::string Record::get_time_stamp(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime(buffer,80,"_%Hh%Ms%S_%d-%m-%y_",timeinfo);
    return std::string(buffer);
}
*/
void Record::string_command2(const std_msgs::String::ConstPtr& msg){
    if(msg->data == "record"){
        //thread = boost::thread(&rosbag::Recorder::run,recorder.get());
        //thread.detach();
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
