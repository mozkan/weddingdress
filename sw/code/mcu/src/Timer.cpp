/**
 * @file Timer.cpp
 *
 * @details Contains the implementation of the Timer class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "Timer.h"


//
// Module Variables
//


namespace mcu {

namespace {

//
// Constants
//

LPC_TIMER_T* kTimers[5] = {
  LPC_TIMER0,
  LPC_TIMER1,
  LPC_TIMER2,
  LPC_TIMER3,
  LPC_TIMER4
};

}


//
// Timer Class Definition
//

Timer::Timer(TimerChannels channel)
  : timer_(kTimers[static_cast<int>(channel)]) {
  Chip_TIMER_Init(timer_);
}

Timer::~Timer() { }

void Timer::SetPrescaler(uint32_t prescaler) {
  Chip_TIMER_PrescaleSet(timer_, prescaler);
}

void Timer::Start(void) {
  Chip_TIMER_Enable(timer_);
}

uint32_t Timer::GetCount(void) {
  return Chip_TIMER_ReadCount(timer_);
}

} // namespace mcu
