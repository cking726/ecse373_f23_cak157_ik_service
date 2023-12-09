#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"
#include "ik_service/PoseIK.h"
#include "ur_kinematics/ur_kin.h"

int main(int argc, char **argv)
{

    ros::init(argc,argv,"ik_client");
    ros::NodeHandle n;

    ik_service::PoseIK pose_ik;
    geometry_msgs::Pose part_pose;


    ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");

    part_pose.position.x = 0.5;
    pose_ik.request.part_pose = part_pose;

    if (client.call(pose_ik))
    {
       ROS_INFO("Call to ik_service returned [%i] solutions",     pose_ik.response.num_sols);
    }
     else
    {
       ROS_ERROR("Failed to call service ik_service");
       return 1;
    }

    return 0;
}