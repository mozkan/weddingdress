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
  enum class InterruptState {
    kEnable = 0,
    kDisable
  };

  /**
   * Constructor for the Timer class.
   *
   * @param[in] timer The hardware timer to control.
   */
  Timer(TimerChannels channel);

  ~Timer();

  /**
   * Sets the prescaler for this timer.
   *
   * @return Nothing.
   */
  void SetPrescaler(uint16_t prescaler);

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
  uint16_t GetCount(void);

  /**
   * Enables the interrupt on completion of a full period
   *
   * @return Nothing.
   */
  void ConfigureTimeoutInterrupt(InterruptState state);

  /**
   * Gets the number of timeouts that have occurred since the timer was started.
   *
   * @return The number of timeouts.
   */
  uint16_t GetTimeouts(void);

  // Disallow copy and assign.
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;

 private:
#if 0
  TimerChannels      timer_channel_;
  LPC_TIMER_T*       timer_;
  LPC11CXX_IRQn_Type irq_;
  uint8_t            match_channel_;
#endif
};

} // namespace mcu

#endif /* TIMER_H_ */
