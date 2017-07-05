#ifndef PINMUX_H_
#define PINMUX_H_

/**
 * @file PinMux.h
 *
 * @details Contains the declaration of the PinMux class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */


namespace mcu {

//
// PinMux Class Declaration
//

/**
 * Encapsulates pin mux configuration and peripheral enables for the MCU/board.
 * Peripherals are active and pin muxing is complete once this object is
 * created.
 */
class PinMux {
 public:
  PinMux();
  ~PinMux();

  // Disallow copy and assign.
  PinMux(const PinMux&) = delete;
  PinMux& operator=(const PinMux&) = delete;
};

} // namespace mcu

#endif /* PINMUX_H_ */
