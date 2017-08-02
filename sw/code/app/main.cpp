#include <cstdint>

#include <array>

#include "Display.h"
#include "Wedfestdress.h"

#include "pattern/PatternHelpers.h"
#include "task/Task.h"
#include "task/PatternRunnerTask.h"


constexpr int kPatternRunnerTaskIntervalMs = 10; // 100 Hz. refresh rate.

constexpr int kTaskCount = 1;

int main(void) {
  // Initialize hardware resources.
  hal::Wedfestdress dress;

  // Create the tasks that will run in the main loop.
  app::task::PatternRunnerTask pattern_runner(dress.GetTiming(),
                                              dress.GetDisplay(),
                                              kPatternRunnerTaskIntervalMs);

  std::array<app::task::Task*, kTaskCount> tasks = {{
    &pattern_runner
  }};

  // Run all tasks.
  while (1) {
    for (auto task : tasks) {
      task->Run();
    }
  }

  return 0;
}
