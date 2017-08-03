#ifndef BUTTON_POLL_TASK_H_
#define BUTTON_POLL_TASK_H_

/**
 * @file ButtonPollTask.h
 *
 * @details Header file for the declaration of the ButtonPollTask class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "Button.h"
#include "Timing.h"

#include "Task.h"


namespace app {
namespace task {

//
// ButtonPollTask Class Declaration
//

/**
 * Task class for checking the user button. Contains a Button which it checks on
 * a timebase managed by the Task mechanism.
 */
class ButtonPollTask : public Task {
 public:
  /**
   * Constructor for the ButtonPollTask class.
   */
  ButtonPollTask(hal::Timing& timing,
                 uint32_t interval_ms,
                 hal::Button& user_button,
                 hal::Button::ReadValue& user_button_value);

  virtual ~ButtonPollTask();

  // Disallow copy and assign.
  ButtonPollTask(const ButtonPollTask&) = delete;
  ButtonPollTask& operator=(const ButtonPollTask&) = delete;

 private:
  void RunTask(void) override;

  hal::Button& user_button_;
  hal::Button::ReadValue& user_button_value_;
};

} // namespace task
} // namespace app

#endif /* BUTTON_POLL_TASK_H_ */
