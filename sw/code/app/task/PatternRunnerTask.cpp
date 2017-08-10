/**
 * @file PatternRunnerTask.cpp
 *
 * @details Contains the implementation of the PatternRunnerTask class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "PatternRunnerTask.h"

#include "../pattern/AlternateRampPattern.h"
#include "../pattern/FlashyDinglerPattern.h"


namespace app {
namespace task {

// TEMP
class AllDarkPattern : public app::pattern::Pattern {
 public:
  AllDarkPattern(hal::Display& display) : app::pattern::Pattern(display) { }
  ~AllDarkPattern() { }

 private:
  void CalculateNextIteration(void) override { }
};
// END TEMP

//
// PatternRunnerTask Public Member Definitions
//

PatternRunnerTask::PatternRunnerTask(hal::Timing& timing,
                                     uint32_t interval_ms,
                                     hal::Display& display,
                                     hal::Button::ReadValue& user_button_value)
  : Task(timing, interval_ms),
    pattern_number_(0),
    patterns_{{
      new AllDarkPattern(display),
      new app::pattern::FlashyDinglerPattern(display),
      new app::pattern::AlternateRampPattern(display),
    }},
    user_button_value_(user_button_value) { }

PatternRunnerTask::~PatternRunnerTask() {
  for (auto pattern : patterns_) {
    delete pattern;
  }
}


//
// Private Member Definitions
//

void PatternRunnerTask::NextPattern(void) {
  pattern_number_++;
  if (pattern_number_ == static_cast<int>(patterns_.size())) {
    pattern_number_ = 0;
  }

  patterns_[pattern_number_]->Reset();
}

void PatternRunnerTask::RunTask(void) {
  // Check button state.
  if (user_button_value_ == hal::Button::ReadValue::kShortPress) {
    // Reset the flag.
    user_button_value_ = hal::Button::ReadValue::kNoPress;

    NextPattern();
  }

  patterns_[pattern_number_]->Update();
}

} // namespace task
} // namespace app
