/// HEADER
#include <path_follower/local_planner/local_planner_null.h>

/// PROJECT
#include <path_follower/pathfollower.h>

LocalPlannerNull::LocalPlannerNull(PathFollower &follower,
                                   tf::Transformer &transformer)
    : LocalPlanner(follower, transformer)
{

}

void LocalPlannerNull::setGlobalPath(Path::Ptr path)
{
    /*
     * this local planner does nothing, so the global path is
     * equal to the local path!
     */
    LocalPlanner::setGlobalPath(path);

    follower_.getController()->setPath(path);
}

Path::Ptr LocalPlannerNull::updateLocalPath(const std::vector<Constraint::Ptr>& constraints,
                                            const std::vector<Scorer::Ptr>& scorer,
                                            const std::vector<bool>& fconstraints,
                                            const std::vector<double>& wscorer,
                                            Path::Ptr& wlp)
{
    (void) constraints;
    (void) scorer;
    (void) fconstraints;
    (void) wscorer;
    (void) wlp;
    // do nothing
    return nullptr;
}

bool LocalPlannerNull::isNull() const
{
    return true;
}

void LocalPlannerNull::setParams(int nnodes, int ic, double dis2p,  double adis, double fdis, double s_angle,
                                 int ia, double lmf, int max_level, double mu, double ef){
    (void) nnodes;
    (void) ic;
    (void) dis2p;
    (void) adis;
    (void) fdis;
    (void) s_angle;
    (void) ia;
    (void) lmf;
    (void) max_level;
    (void) mu;
    (void) ef;
}

void LocalPlannerNull::setVelocity(geometry_msgs::Twist::_linear_type vector){
    (void) vector;
}

void LocalPlannerNull::setVelocity(double velocity){
    (void) velocity;
}
