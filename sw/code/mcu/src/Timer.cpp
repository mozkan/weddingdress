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
#if 0
static uint16_t timer16_1_timeouts = 0;
#endif


namespace mcu {

namespace {

//
// Types
//
#if 0
struct TimerParams {
  LPC_TIMER_T*       timer;
  int8_t             match_ch;
  LPC11CXX_IRQn_Type irq;
  uint16_t*          timeouts;
};
#endif


//
// Constants
//

#if 0
const TimerParams kTimers[1] = {
  { LPC_TIMER16_1, 3, TIMER_16_1_IRQn, &timer16_1_timeouts }, //kCT16B1
};
#endif

}


//
// Timer Class Definition
//

Timer::Timer(TimerChannels /*channel*/)
#if 0
  : timer_channel_(channel),
    timer_(kTimers[static_cast<int>(channel)].timer),
    irq_(kTimers[static_cast<int>(channel)].irq),
    match_channel_(kTimers[static_cast<int>(channel)].match_ch)
#endif
{
#if 0
  Chip_TIMER_Init(timer_);

  // Set the period to full scale for this timer.
  Chip_TIMER_SetMatch(timer_, match_channel_, 0xFFFF);
#endif
}

Timer::~Timer() { }

void Timer::SetPrescaler(uint16_t /*prescaler*/) {
#if 0
  // Set prescaler.
  Chip_TIMER_PrescaleSet(timer_, static_cast<uint32_t>(prescaler));
#endif
}

void Timer::Start(void) {
#if 0
  Chip_TIMER_Enable(timer_);
#endif
}

uint16_t Timer::GetCount(void) {
#if 0
  return static_cast<uint16_t>(Chip_TIMER_ReadCount(timer_));
#endif
  return 0;
}

void Timer::ConfigureTimeoutInterrupt(InterruptState /*state*/) {
#if 0
  if (state == InterruptState::kEnable) {
    NVIC_EnableIRQ(irq_);
    Chip_TIMER_MatchEnableInt(timer_, match_channel_);
  }
  else {
    NVIC_DisableIRQ(irq_);
    Chip_TIMER_MatchDisableInt(timer_, match_channel_);
  }
#endif
}

uint16_t Timer::GetTimeouts(void) {
#if 0
  return *kTimers[static_cast<int>(timer_channel_)].timeouts;
#endif
  return 0;
}

} // namespace mcu


extern "C" {

void TIMER16_1_IRQHandler(void) {
#if 0
  // Clear match interrupt flag.
  LPC_TIMER16_1->IR = 0x8;

  timer16_1_timeouts++;
#endif
}

}
