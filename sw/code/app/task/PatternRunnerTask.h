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

#include "Button.h"
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
                    uint32_t interval_ms,
                    hal::Display& display,
                    hal::Button::ReadValue& user_button_value);

  virtual ~PatternRunnerTask();

  // Disallow copy and assign.
  PatternRunnerTask(const PatternRunnerTask&) = delete;
  PatternRunnerTask& operator=(const PatternRunnerTask&) = delete;

 private:
  static const int kPatternCount = 3;

  void NextPattern(void);
  void RunTask(void) override;

  int pattern_number_;
  const std::array<app::pattern::Pattern*, kPatternCount> patterns_;
  hal::Button::ReadValue& user_button_value_;
};

} // namespace task
} // namespace app

#endif /* PATTERN_RUNNER_TASK_H_ */
