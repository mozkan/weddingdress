#ifndef TASK_H_
#define TASK_H_

/**
 * @file Task.h
 *
 * @details Header file for the declaration of the Task class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "Timing.h"


namespace app {
namespace task {

//
// Task Class Declaration
//

/**
 * Abstrat class representing a timed task. Allows for arbitrary work to be done
 * on a fixed time-base via its specializations.
 */
class Task {
 public:
  /**
   * Constructor for the Task class.
   *
   * @param[in] timing The timing resource class to manage timing functions.
   * @param[in] interval_ms The execution interval in milliseconds for this
   *     task.
   */
  Task(hal::Timing& timing, uint32_t interval_ms);

  virtual ~Task();

  /**
   * Runs the task. If its timing interval has elapsed, the task will run.
   * Otherwise it will skip this iteration. This function can be called at an
   * arbitrary rate. If it is called too slowly it will miss its deadline.
   *
   * @return Nothing.
   */
  void Run(void);

  // Disallow copy and assign.
  Task(const Task&) = delete;
  Task& operator=(const Task&) = delete;

 protected:
  virtual void RunTask(void) = 0;

 private:
  const uint32_t kIntervalMs;

  hal::Timing& timing_;
  uint32_t     last_millis_;
};

} // namespace task
} // namespace app

#endif /* TASK_H_ */
