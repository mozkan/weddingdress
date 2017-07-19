/**
 * @file PinMux.cpp
 *
 * @details Contains the Implementation of the PinMux class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "chip.h"

#include "fault.h"

#include "LPCOpenCfg.h"
#include "PinMux.h"

namespace mcu {

//
// PinMux Class Definition
//

PinMux::PinMux() {
  Chip_GPIO_Init(LPC_GPIO);
  ASSERT(Chip_SPI_Init(LPC_SPI0) == 0);
  ASSERT(Chip_SPI_Init(LPC_SPI1) == 0);

  Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_IOCON);

  // CLKOUT pin.
  Chip_IOCON_PinMux(LPC_IOCON, 0, 21,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_GPIO_MODE |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC1);

  // Configure Type I GPIO (no push-pull output).
  Chip_IOCON_PinMux(LPC_IOCON, 0, 23,
                    (IOCON_GPIO_MODE |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON |
                     IOCON_STDI2C_EN),
                    IOCON_FUNC0); // STRING1_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 24,
                    (IOCON_GPIO_MODE |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON |
                     IOCON_STDI2C_EN),
                    IOCON_FUNC0); // STRING2_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 25,
                    (IOCON_GPIO_MODE |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON |
                     IOCON_STDI2C_EN),
                    IOCON_FUNC0); // STRING3_EN.

  // Configure Type D GPIO.
  Chip_IOCON_PinMux(LPC_IOCON, 0, 2,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // LED_PWR_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 11,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // STRING4_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 12,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // STRING5_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 13,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // STRING6_EN.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 14,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // GREEN_LED1.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 15,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // GREEN_LED2.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 18,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC0); // RED_LED1.

  // Configure SPI0 (FlexComm 0).
  Chip_IOCON_PinMux(LPC_IOCON, 0, 22,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC2); // FC0_MOSI.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 20,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC2); // FC0_SCK.

  // Configure SPI2 (FlexComm 2).
  Chip_IOCON_PinMux(LPC_IOCON, 0, 8,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC1); // FC2_MOSI.

  Chip_IOCON_PinMux(LPC_IOCON, 0, 10,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC1); // FC2_SCK.
}

PinMux::~PinMux() { }

} // namespace mcu
