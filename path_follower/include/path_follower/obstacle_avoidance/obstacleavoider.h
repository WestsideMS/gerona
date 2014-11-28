#ifndef OBSTACLEAVOIDER_H
#define OBSTACLEAVOIDER_H

#include <Eigen/Core>
#include <pcl_ros/point_cloud.h>
#include <tf/tf.h>

#include <path_follower/pathfollowerparameters.h>
#include <path_follower/utils/path.h>

class ObstacleAvoider
{
public:
    typedef pcl::PointXY ObstaclePoint;
    typedef pcl::PointCloud<ObstaclePoint> ObstacleCloud;

    //! Additional information about the robots state, that might be required by the obstacle avodier
    struct State
    {
        //! Current path
        const Path::ConstPtr path;

        const PathFollowerParameters &parameters;

        State(const Path::ConstPtr path, const PathFollowerParameters &parameters):
            path(path),
            parameters(parameters)
        {}
    };

    /**
     * @brief Determines, if there are obstacles, which are blocking the path and adjusts the
     *        move command such that a collision is avoided.
     * @param cmd       The move command. Can be modified by the method to avoid collisions.
     * @param obstacles Point cloud that holds detected obstacles (e.g. a laser scan)
     * @param state     Additional information about the current state of the robot.
     * @return True, if the move command was modified, otherwise false.
     */
    virtual bool avoid(tf::Vector3* const cmd, ObstacleCloud::ConstPtr obstacles, const State &state) = 0;
};

#endif // OBSTACLEAVOIDER_H
