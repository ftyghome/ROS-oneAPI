#include "ros/ros.h"
#include "prog.hpp"
#include "ros_oneapi/vector.h"

clComputeModule cl_module;

bool vec_add(ros_oneapi::vector::Request  &req,
             ros_oneapi::vector::Response &res )
{
    cl_module.vecAdd(req.a.data.data(),req.b.data.data());
    res.sum.data = req.a.data;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vec_add_node");
    ROS_INFO("Vector add example node started.");

    ROS_INFO("%s",(std::string("OneAPI running on device: ") + cl_module._getDeviceInfo()).c_str());
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("ros_oneapi/vec_add", vec_add);
    ros::spin();
    return 0;
}