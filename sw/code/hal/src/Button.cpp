/**
 * @file Button.cpp
 *
 * @details Contains the implementation of the Button class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "Button.h"

#include "fault.h"


namespace hal {

//
// Button Class Definition
//

Button::Button(mcu::GPIOPin& user_button, Timing& timing)
  : button_gpio_(user_button),
    timing_(timing),
    state_(State::kIdle),
    start_time_(0),
    detected_input_(ReadValue::kNoPress) { }

Button::~Button() { }

Button::ReadValue Button::Read(void) {
  // Run another iteration of the UI detection state machine.
  RunStateMachine();

  // Clear the last detected value so subsequent calls do not return false
  // positives.
  ReadValue read_val = ReadValue::kNoPress;
  if (detected_input_ != ReadValue::kNoPress) {
    read_val = detected_input_;
    detected_input_ = ReadValue::kNoPress;
  }
  
  return read_val;
}


//
// Private Function Definitions
//

void Button::RunStateMachine(void) {
  switch (state_) {
    case State::kIdle:
      ExecuteStateIdle();
    break;

    case State::kPressedDebouncing:
      ExecuteStatePressedDebouncing();
    break;

    case State::kPressedDebounced:
      ExecuteStatePressedDebounced();
    break;

    case State::kReleasedDebouncing:
      ExecuteStateReleasedDebouncing();
    break;

    default:
      ASSERT(false);
    break;

  }
}

void Button::SetNextState(void) {
  state_++;
  if (state_ == State::kNumStates) {
    state_ = State::kIdle;
  }
}

void Button::ResetStateMachine(void) {
  state_ = static_cast<int>(State::kIdle);
}

void Button::ExecuteStateIdle(void) {
  if (ButtonIsPressed()) {
    start_time_ = timing_.Millis();
    SetNextState();
  }
}

void Button::ExecuteStatePressedDebouncing(void) {
  if ((timing_.Millis() - start_time_) >= kDebounceIntervalMs) {
    if (ButtonIsPressed()) {
      SetNextState();
    }
    else {
      // Input was a glitch, reset state machine.
      ResetStateMachine();
    }
  }
}

void Button::ExecuteStatePressedDebounced(void) {
  if (!ButtonIsPressed()) {
    start_time_ = timing_.Millis(); // Restart stopwatch.
    SetNextState();
  }
  else {
    if ((timing_.Millis() - start_time_) >= kLongPressDurationMs) {
      detected_input_ = ReadValue::kLongPress;
      ResetStateMachine();
    }
  }
}

void Button::ExecuteStateReleasedDebouncing(void) {
  if ((timing_.Millis() - start_time_) >= kDebounceIntervalMs) {
    detected_input_ = ReadValue::kShortPress;
    ResetStateMachine();
  }
}

bool Button::ButtonIsPressed(void) {
  return button_gpio_.ReadInput() == mcu::GPIOPin::GPIOValue::Low;
}

} // namespace hal
