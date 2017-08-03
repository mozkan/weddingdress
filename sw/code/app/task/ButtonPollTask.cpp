/**
 * @file ButtonPollTask.cpp
 *
 * @details Contains the implementation of the ButtonPollTask class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "ButtonPollTask.h"


namespace app {
namespace task {

//
// ButtonPollTask Public Member Definitions
//

ButtonPollTask::ButtonPollTask(hal::Timing& timing,
                               uint32_t interval_ms,
                               hal::Button& user_button,
                               hal::Button::ReadValue& user_button_value)
  : Task(timing, interval_ms),
    user_button_(user_button),
    user_button_value_(user_button_value) { }

ButtonPollTask::~ButtonPollTask() { }


//
// Private Member Definitions
//

void ButtonPollTask::RunTask(void) {
  hal::Button::ReadValue button_value = user_button_.Read();

  // Only set the externally visible button value of it is not idle. This
  // requires the consumer of the button value to reset it.
  if (button_value != hal::Button::ReadValue::kNoPress) {
    user_button_value_ = button_value;
  }
}

} // namespace task
} // namespace app
