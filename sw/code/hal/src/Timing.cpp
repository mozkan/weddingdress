/**
 * @file Timing.cpp
 *
 * @details Contains the implementation of the Timing class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "MCUConfig.h"

#include "Timing.h"


namespace hal {

//
// Timing Class Definition
//

Timing::Timing(mcu::Timer& timer) : timer_(timer) {
  // Configure for 1 millisecond ticks.
  //timer_.SetPrescaler(mcu::kCPUClockHz / 1000);

  // Start the timer.
  //timer_.Start();
}

Timing::~Timing() { }

uint32_t Timing::Millis(void)
{
  //return timer_.GetCount() + (timer_.GetTimeouts() * 0xFFFF);
  return 0; // Temporary
}

} // namespace hal
