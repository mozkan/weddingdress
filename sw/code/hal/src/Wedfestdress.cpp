/**
 * @file Wedfestdress.cpp
 *
 * @details Implementation of the Wedfestdress class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "fault.h"

#include "MCUConfig.h"

#include "Wedfestdress.h"


namespace hal {

//
// Wedfestdress Class Definition
//

bool Wedfestdress::initialized_ = false;

Wedfestdress::Wedfestdress()
  : mcu_(),
    display_(mcu_.GetSPIMaster(mcu::SPIPeripherals::kSPI0),
             mcu_.GetSPIMaster(mcu::SPIPeripherals::kSPI1),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_23),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_24),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_25),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_11),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_12),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_13),
             mcu_.GetGPIOPin(mcu::GPIOPins::kPIO0_2)),
     timing_(mcu_.GetTimerChannel(mcu::TimerChannels::kCTimer0)) {
  ASSERT(initialized_ == false);
  initialized_ = true;
}

Wedfestdress::~Wedfestdress() { }

Display& Wedfestdress::GetDisplay(void) {
  return display_;
}

Timing& Wedfestdress::GetTiming(void) {
  return timing_;
}

#if 0
Microphone& Wedfestdress::GetMicrophone(void) {
  return microphone_;
}

UserInput& Wedfestdress::GetUserInput(void) {
  return user_input_;
}

Battery& Wedfestdress::GetBattery(void) {
  return battery_;
}
#endif
} // namespace hal
