#include <cstdint>

#include <array>

#include "Button.h"
#include "Display.h"
#include "Wedfestdress.h"

#include "task/ButtonPollTask.h"
#include "task/Task.h"
#include "task/PatternRunnerTask.h"


constexpr int kPatternRunnerTaskIntervalMs = 10; // 100 Hz. refresh rate.
constexpr int kButtonPollTaskIntervalMs    = 2;

constexpr int kTaskCount = 2;

int main(void) {
  // Initialize hardware resources.
  hal::Wedfestdress dress;

  // Shared variable for passing button state to tasks. Set by the
  // ButtonPollTask and cleared by the PatternRunnerTask.
  // TODO: Replace with callback mechanism.
  hal::Button::ReadValue user_button_value = hal::Button::ReadValue::kNoPress;

  // Create the tasks that will run in the main loop.
  app::task::PatternRunnerTask pattern_runner_task(dress.GetTiming(),
                                                   kPatternRunnerTaskIntervalMs,
                                                   dress.GetDisplay(),
                                                   user_button_value);
  app::task::ButtonPollTask button_poll_task(dress.GetTiming(),
                                             kButtonPollTaskIntervalMs,
                                             dress.GetUserButton(),
                                             user_button_value);
                                        

  std::array<app::task::Task*, kTaskCount> tasks = {{
    &pattern_runner_task,
    &button_poll_task
  }};

  // Temporary for wedding. Wait until button is pressed before running the
  // first pattern. Will press when we kiss after the ceremony.
  //hal::Button& user_button = dress.GetUserButton();
  //while (user_button.Read() == hal::Button::ReadValue::kNoPress) { }
  // End temporary wedding.

  // Run all tasks.
  while (1) {
    for (auto task : tasks) {
      task->Run();
    }
  }

  return 0;
}
