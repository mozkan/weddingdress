#ifndef PWM16_H_
#define PWM16_H_

/**
 * @file PWM16.h
 *
 * @details Contains the declaration of the PWM16 class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "MCUConfig.h"


namespace mcu {

//
// PWM16 Class Declaration
//

/**
 * Driver class encapsulating a simple 16-bit PWM peripheral with a fixed
 * period.
 */
class PWM16 {
 public:
  enum class InterruptState {
    kEnable = 0,
    kDisable
  };

  /**
   * Constructor for the PWM16 class. Configures and starts the PWM output.
   *
   * @param[in] timer The hardware timer to derive this PWM from.
   * @param[in] channel The compare/match channel for the given timer to use for
   *     generating this PWM.
   */
  PWM16(PWMChannels channel);

  ~PWM16();

  /**
   * Stops the PWM's internal timer, stopping the outputs from changing state.
   *
   * @return Nothing.
   */
  void Stop(void);

  /**
   * Restarts the PWM from the beginning of a cycle.
   *
   * @return Nothing.
   */
  void Restart(void);

  /**
   * Sets the PWM duty cycle.
   *
   * @param[in] dutycycle The duty cycle as a fraction of 0xFFFF.
   * @return Nothing.
   */
  void SetDutyCycle(uint16_t dutycycle);

  /**
   * Enables or disables the interrupt that occurs when the PWM has completed a
   * cycle.
   *
   * @param[in] state Enables/disables this interrupt.
   * @see InterruptState.
   */
  void ConfigureEndOfPeriodInterrupt(InterruptState state);

  // Disallow copy and assign.
  PWM16(const PWM16&) = delete;
  PWM16& operator=(const PWM16&) = delete;

 private:
#if 0
  PWMChannels        channel_;
  LPC_TIMER_T*       timer_;
  int8_t             output_match_ch_;
  int8_t             reset_match_ch_;
  LPC11CXX_IRQn_Type irq_;
#endif
};

} // namespace mcu

#endif /* PWM16_H_ */

