#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

/**
 * @file MCUConfig.h
 *
 * @details MCU peripheral configuration file. Defines the availability of
 *     peripherals on this MCU and board.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>


namespace mcu {

//
// MCU Parameters
//

constexpr uint32_t kCPUClockHz = 100000000;


//
// Peripheral Declarations
//

// GPIO pins on this board
enum class GPIOPins {
  kPIO0_2 = 0,
  kPIO0_11,
  kPIO0_12,
  kPIO0_13,
  kPIO0_14,
  kPIO0_15,
  kPIO0_18,
  kPIO0_19,
  kPIO0_23,
  kPIO0_24,
  kPIO0_25,
  kPIO1_17
};

enum class SPIPeripherals {
  kSPI0FC0 = 0,
  kSPI1FC2
};

// PWM outputs on this board
enum class PWMChannels {
#if 0
  kCT16B0Mat0 = 0,
  kCT16B0Mat1,
  kCT32B0Mat0,
  kCT32B0Mat1,
  kCT32B1Mat0,
  kCT32B1Mat1
#endif
};

enum class TimerChannels {
#if 0
  kCT16B1 = 0
#endif
};

enum class ADCChannels {
#if 0
  kAD6 = 0,
  kAD7
#endif
};

} // namespace mcu

#endif /* MCU_CONFIG_H_ */
