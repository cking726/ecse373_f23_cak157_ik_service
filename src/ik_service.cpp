#include "ros/ros.h"
#include "std_msgs/String.h" 
#include "ik_service/PoseIK.h"
#include "ik_service/JointSolutions.h"
#include "ur_kinematics/ur_kin.h"

// Service function
bool pose_ik(ik_service::PoseIK::Request &req, ik_service::PoseIK::Response &res)
{   
    
    // Second, 2D way to define the same T Matrix
    double T[4][4] = {{0.0, -1.0, 0.0, req.part_pose.position.x}, \
    {0.0, 0.0, 1.0, req.part_pose.position.y}, \
    {-1.0, 0.0, 0.0 , req.part_pose.position.z}, \
    {0.0, 0.0, 0.0, 1.0}};
    // Variable to receive the number of solutions returned
    int num_sol;
    // Allocate space for up to eight solutions of six joint angles
    float q_sols[8][6];
    // Inverse kinematic solution(s)
    num_sol = ur_kinematics::inverse(&T[0][0], (double *)&q_sols[0][0], 0.0);
    // The last element is the required precision of the solutions.

    return true;
}


int main(int argc, char  *argv[])
{   
    
    ros::init(argc,argv,"pose_ik_service");
    ros::NodeHandle n;
    

    ros::ServiceServer service = n.advertiseService("pose_ik", pose_ik);

    ROS_INFO("PoseIK service is now working.");

    ros::spin();


    return 0;
}