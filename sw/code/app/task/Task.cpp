/**
 * @file Task`.cpp
 *
 * @details Contains the implementation of the Task class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "Task.h"


namespace app {
namespace task {

//
// Task Class Definition
//

Task::Task(hal::Timing& timing, uint32_t interval_ms)
  : kIntervalMs(interval_ms), timing_(timing) { }

Task::~Task() { }

void Task::Run() {
  uint32_t now = timing_.Millis();
  if ((now - last_millis_) >= kIntervalMs) {
    last_millis_ = now;
    RunTask();
  }
}

} // namespace task
} // namespace app
