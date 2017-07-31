#ifndef TIMER_H_
#define TIMER_H_

/**
 * @file Timer.h
 *
 * @details Contains the declaration of the Timer class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "chip.h"

#include "MCUConfig.h"


namespace mcu {

//
// Timer Class Declaration
//

/**
 * Driver class encapsulating a simple timer peripheral derived from the CPU
 * clock.
 */
class Timer {
 public:
  /**
   * Constructor for the Timer class.
   *
   * @param[in] timer The hardware timer to control.
   */
  Timer(TimerChannels channel);

  ~Timer();

  /**
   * Sets the prescaler value for this timer.
   *
   * @return Nothing.
   */
  void SetPrescaler(uint32_t prescaler);

  /**
   * Starts the timer.
   *
   * @return Nothing.
   */
  void Start(void);

  /**
   * Gets the current timer count.
   *
   * @return The current count.
   */
  uint32_t GetCount(void);

  // Disallow copy and assign.
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
 
 private:
  LPC_TIMER_T* timer_;
};

} // namespace mcu

#endif /* TIMER_H_ */
