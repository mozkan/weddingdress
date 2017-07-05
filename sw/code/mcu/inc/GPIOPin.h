#ifndef GPIOPIN_H_
#define GPIOPIN_H_

/**
 * @file GPIOPin.h
 *
 * @details Header file for the declaration of the GPIOPin peripheral driver
 * class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "MCUConfig.h"


namespace mcu {

//
// GPIOPin Class Declaration
//

/**
 * Class representing a single GPIO pin.
 */
class GPIOPin {
 public:
  enum class GPIOValue {
    High = 0,
    Low  = 1
  };

  enum class GPIODirection {
    Output = 0,
    Input  = 1
  };

  /**
   * Constructor for the GPIOPin class.
   *
   * @param[in] pin The PIO number for this GPIO pin.
   * @param[in] direction Determines the initial state of the GPIO pin.
   */
  GPIOPin(GPIOPins pin, GPIODirection direction);

  ~GPIOPin();

  /**
   * Sets an output pin to a logic-high state.
   * @return Nothing.
   */
  void Set(void);

  /**
   * Sets an output pin to a logic-low state.
   * @return Nothing.
   */
  void Clear(void);

  /**
   * Sets an output pin to a user-provided logic value. An alternative means of
   * setting the output state compared to the explicit Set() and Clear()
   * functions.
   *
   * @param[in] value The logic value to set on the pin.
   * @return Nothing.
   */
  void SetOutput(GPIOValue value);

  /**
   * Reads the logic value present on an input pin.
   * @return GPIOValue representing the logic value on the pin.
   */
  GPIOValue ReadInput(void);

  /**
   * Sets the direction of the GPIO pin.
   *
   * @param[in] direction The direction to configure the pin.
   * @return Nothing.
   */
  void SetDirection(GPIODirection direction);

  // Disallow copy and assign.
  GPIOPin(const GPIOPin&) = delete;
  GPIOPin& operator=(const GPIOPin&) = delete;

 private:
  uint8_t port_;
  uint8_t bit_;
};

} // namespace mcu

#endif /* GPIOPIN_H_ */
