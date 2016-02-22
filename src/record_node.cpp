#include "record_ros/record.h"

#include <ros/ros.h>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

int main(int argc, char** argv)
{

    ros::init(argc, argv,"");
    ros::NodeHandle nh;

    std::string topic, path_save, file_name;
    if (!nh.getParam("/record/topic", topic))
    {
        ROS_WARN("no topic param found");
    }
    if (!nh.getParam("/record/path_save", path_save))
    {
        ROS_WARN("no path_save param found");
    }else{
        boost::filesystem::path config_folder(path_save);
        if( !(boost::filesystem::exists(config_folder)))
        {
            ROS_WARN_STREAM("TARGET directory to save bag not found,.. make sure this path [" << path_save << "] exists");
        }
    }
    if (!nh.getParam("/record/file_name", file_name))
    {
        ROS_WARN("file_name param found");
    }


    // split topics with space (use regrex)
    ROS_INFO("Starting record node");
    ROS_INFO_STREAM("topics:    "   << topic);
    ROS_INFO_STREAM("name:      "   << path_save);
    ROS_INFO_STREAM("file_name: "   << file_name);

    // Extract all topics white space seperated
    boost::regex rgx("\\s+");
    boost::sregex_token_iterator iter(topic.begin(), topic.end(),rgx,-1);
    boost::sregex_token_iterator end;
    std::vector<std::string> topics;
    for ( ; iter != end; ++iter){
        topics.push_back(*iter);
        std::cout << *iter << '\n';
    }

    rosbag::RecorderOptions options;
    options.topics = topics;
    options.prefix = path_save + "/" + file_name;

    Record* record = new Record(nh,options);
    record->wait_for_callback();
    record->run();


    return 0;
}
