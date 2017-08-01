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


namespace app {
namespace task {

//
// PatternRunnerTask Public Member Definitions
//

PatternRunnerTask::PatternRunnerTask(hal::Timing& timing,
                                     hal::Display& display,
                                     uint32_t interval_ms) 
  : Task(timing, interval_ms),
    pattern_number_(0),
    patterns_{{
      new app::pattern::AlternateRampPattern(display)
    }} { }

PatternRunnerTask::~PatternRunnerTask() {
  for (auto pattern : patterns_) {
    delete pattern;
  }
}

void PatternRunnerTask::NextPattern(void) {
  pattern_number_++;
  if (pattern_number_ == static_cast<int>(patterns_.size())) {
    pattern_number_ = 0;
  }
}


//
// Private Member Definitions
//

void PatternRunnerTask::RunTask(void) {
  patterns_[pattern_number_]->Update();
}

} // namespace task
} // namespace app
