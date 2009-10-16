/* Generated by Together */
#ifndef ORDEREDTASK_H
#define ORDEREDTASK_H

#include "Tasks/AbstractTask.h"
#include "BaseTask/OrderedTaskPoint.hpp"
#include "BaseTask/StartPoint.hpp"
#include "BaseTask/TaskLeg.h"
#include <vector>
#include "Util/Serialisable.hpp"
#include "GlideSolvers/MacCready.hpp"

class OrderedTask:
  public AbstractTask,
  public Serialisable
{
public:
  OrderedTask(const TaskEvents &te, TaskAdvance &ta);
  ~OrderedTask();

  std::vector<TaskLeg*> legs;

  TaskPoint* getActiveTaskPoint();
  virtual void setActiveTaskPoint(unsigned);

  void insert(OrderedTaskPoint*, unsigned position);
  void remove(unsigned position);

  virtual bool update_sample(const AIRCRAFT_STATE &, const bool full_update);

  virtual bool update_idle(const AIRCRAFT_STATE&);

  unsigned task_size() const {
    return tps.size();
  }

  // these used by task dijkstra
  const SearchPointVector& get_tp_search_points(unsigned tp) const {
    return tps[tp]->get_search_points();
  }
  void set_tp_search_min(unsigned tp, const SearchPoint &sol) {
    tps[tp]->set_search_min(sol);
  }
  void set_tp_search_max(unsigned tp, const SearchPoint &sol) {
    tps[tp]->set_search_max(sol);
  }
  virtual void report(const AIRCRAFT_STATE &state);

protected:
  virtual bool check_transitions(const AIRCRAFT_STATE &, const AIRCRAFT_STATE&);
  double scan_distance_nominal();
  double scan_distance_planned();
  double scan_distance_remaining(const GEOPOINT &location);
  double scan_distance_scored(const GEOPOINT &location);
  double scan_distance_travelled(const GEOPOINT &location);
  void scan_distance_minmax(const GEOPOINT &location, bool full,
                            double *dmin, double *dmax);

private:

  std::vector<OrderedTaskPoint*> tps;

  void update_geometry();

  /**
   * @supplierCardinality 1 
   */
  StartPoint *ts;

  TaskProjection task_projection;

protected:

  virtual double scan_total_start_time(const AIRCRAFT_STATE &);
  virtual double scan_leg_start_time(const AIRCRAFT_STATE &);

  void glide_solution_remaining(const AIRCRAFT_STATE &, 
                                const double mc,
                                GLIDE_RESULT &total,
                                GLIDE_RESULT &leg);

  void glide_solution_travelled(const AIRCRAFT_STATE &, 
                                const double mc,
                                GLIDE_RESULT &total,
                                GLIDE_RESULT &leg);

  void glide_solution_planned(const AIRCRAFT_STATE &, 
                              const double mc,
                              GLIDE_RESULT &total,
                              GLIDE_RESULT &leg,
                              DistanceRemainingStat &total_remaining_effective,
                              DistanceRemainingStat &leg_remaining_effective,
                              const double total_t_elapsed,
                              const double leg_t_elapsed);

  double calc_mc_best(const AIRCRAFT_STATE &, 
                      const double mc);

  double calc_cruise_efficiency(const AIRCRAFT_STATE &aircraft, 
                                const double mc);

  double calc_min_target(const AIRCRAFT_STATE &, 
                         const double mc,
                         const double t_target);
};

#endif //ORDEREDTASK_H
