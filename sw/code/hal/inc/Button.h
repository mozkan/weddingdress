#ifndef BUTTON_H_
#define BUTTON_H_

/**
 * @file Button.h
 *
 * @details Contains the declaration of the Button class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include <cstdint>

#include "GPIOPin.h"

#include "Timing.h"


namespace hal {

//
// Button Class Declaration
//

/**
 * Driver class to represent a momentary push button. Provides a means to
 * reliably read a button prone to bouncing. Hides timing logic for debouncing,
 * detecting short presses, and detecting long presses.
 */
class Button
{
 public:
  enum class ReadValue {
    kNoPress = 0,  //! The button is not being pressed.
    kShortPress,   //! The button was pressed momentarily.
    kLongPress     //! The button was pressed and held.
  };

  /**
   * Constructor for the Button class.
   *
   * @param[in] user_button The GPIO that the user button is connected to.
   * @param[in] timing Timing resource.
   */
  Button(mcu::GPIOPin& user_button, Timing& timing);

  ~Button();

  /**
   * Reads the state of the user button. This function should be used in a
   * button polling loop. Its accuracy is subject to the sampling interval of
   * the button, which is directly related to the frequency with which this
   * function is called.
   *
   * @return The state of the user button.
   */
  ReadValue Read(void);

  // Disallow copy and assign.
  Button(const Button&) = delete;
  Button& operator=(const Button&) = delete;

 private:
  static const uint32_t kDebounceIntervalMs  = 10;
  static const uint32_t kLongPressDurationMs = 400;

  enum State {
    kIdle = 0,
    kPressedDebouncing,
    kPressedDebounced,
    kReleasedDebouncing,
    kNumStates
  };

  void RunStateMachine(void);
  void SetNextState(void);
  void ResetStateMachine(void);
  void ExecuteStateIdle(void);
  void ExecuteStatePressedDebouncing(void);
  void ExecuteStatePressedDebounced(void);
  void ExecuteStateReleasedDebouncing(void);
  bool ButtonIsPressed(void);

  mcu::GPIOPin&   button_gpio_;
  Timing&         timing_;
  int             state_;
  uint32_t        start_time_;
  ReadValue       detected_input_;
};

} // namespace hal
#endif /* USER_INPUT_H_ */
