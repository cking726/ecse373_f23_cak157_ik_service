#include "ros/ros.h"
#include "std_msgs/String.h" 
#include "ik_service/PoseIK.h"
#include "ik_service/JointSolutions.h"
#include "ur_kinematics/ur_kin.h"

// Service function
bool pose_ik(ik_service::PoseIK::Request &req,
             ik_service::PoseIK::Response &res)
{   
    double q[] = {3.14, -1.13, 1.51, 3.77, -1.51, 0};
    double T[4][4] = {{0.0, -1.0, 0.0, req.part_pose.position.x}, \
                      {0.0, 0.0, 1.0, req.part_pose.position.y}, \
                      {-1.0, 0.0, 0.0 , req.part_pose.position.z}, \
                      {0.0, 0.0, 0.0, 1.0}};
    int num_sol;
    float q_sols[8][6];
    num_sol = ur_kinematics::inverse(&T[0][0], (double *)&q_sols[0][0], 0.0);

    return true;
}


int main(int argc, char **argv)
{   
    
    ros::init(argc,argv,"pose_ik_service");
    ros::NodeHandle n;
    

    ros::ServiceServer service = n.advertiseService("pose_ik", pose_ik);

    ROS_INFO("PoseIK service is now working.");

    ros::spin();


    return 0;
}