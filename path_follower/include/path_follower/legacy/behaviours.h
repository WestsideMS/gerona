#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include <ros/ros.h>

#include <path_follower/pathfollower.h>
#include <path_follower/utils/visualizer.h>
#include <utils_general/Line2d.h>

class Behaviour
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    virtual ~Behaviour() {}

    virtual Behaviour* execute(int* status) = 0;

    void setStatus(int status);

protected:
    PathFollower& parent_;
    RobotController* controller_;
    int* status_ptr_;

    //! Pose of the next waypoint in map frame.
    geometry_msgs::PoseStamped next_wp_map_;

    //! Pose of the next waypoint in robot frame.
    Vector3d next_wp_local_;

    Visualizer* visualizer_;


    Behaviour(PathFollower& parent);

    const SubPath &getCurrentSubPath();
    size_t getSubPathCount() const;
    PathFollowerParameters& getOptions();
    double distanceTo(const Waypoint& wp);

    Behaviour *initExecute(int *status);

    Path::Ptr getPath();

    virtual bool isLeavingPathAllowed() const
    {
        return false;
    }

    virtual Behaviour* selectNextWaypoint()
    {
        return this;
    }
};




struct BehaviourEmergencyBreak : public Behaviour
{
    BehaviourEmergencyBreak(PathFollower& parent)
        : Behaviour(parent)
    {
        // stop immediately
        controller_->stopMotion();
    }

    Behaviour* execute(int *status)
    {
        ROS_WARN("commencing emergency break");
        *status = path_msgs::FollowPathResult::RESULT_STATUS_INTERNAL_ERROR;
        return nullptr;
    }
};




struct BehaviourOnLine : public Behaviour
{
    BehaviourOnLine(PathFollower &parent);
    Behaviour* execute(int *status);
    Behaviour *selectNextWaypoint();
};


struct BehaviourApproachTurningPoint : public Behaviour
{
    BehaviourApproachTurningPoint(PathFollower &parent);

    Behaviour* execute(int *status);

    bool checkIfDone();

    Behaviour *handleDone();

    Behaviour* selectNextWaypoint();

    bool done_;
};


#endif // BEHAVIOURS_H