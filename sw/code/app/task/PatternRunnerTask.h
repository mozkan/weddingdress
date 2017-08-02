#ifndef PATTERN_RUNNER_TASK_H_
#define PATTERN_RUNNER_TASK_H_

/**
 * @file PatternRunnerTask.h
 *
 * @details Header file for the declaration of the PatternRunnerTask class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include <array>

#include "Display.h"
#include "Timing.h"

#include "../pattern/Pattern.h"
#include "Task.h"


namespace app {
namespace task {

//
// PatternRunnerTask Class Declaration
//

/**
 * Task class for running patterns. Will calculate the pattern output and update
 * the display on this task's timebase.
 */
class PatternRunnerTask : public Task {
 public:
  /**
   * Constructor for the PatternRunnerTask class.
   */
  PatternRunnerTask(hal::Timing& timing,
                    hal::Display& display,
                    uint32_t interval_ms);

  virtual ~PatternRunnerTask();

  // Disallow copy and assign.
  PatternRunnerTask(const PatternRunnerTask&) = delete;
  PatternRunnerTask& operator=(const PatternRunnerTask&) = delete;

 private:
  static const int kPatternCount = 1;

  void NextPattern(void);
  virtual void RunTask(void);

  int pattern_number_;
  const std::array<app::pattern::Pattern*, kPatternCount> patterns_;
};

} // namespace task
} // namespace app

#endif /* PATTERN_RUNNER_TASK_H_ */
