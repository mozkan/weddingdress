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

#include "PinMux.h"


namespace mcu {

//
// PinMux Class Definition
//

PinMux::PinMux() {
  Chip_GPIO_Init(LPC_GPIO);

  Chip_Clock_EnablePeriphClock(SYSCON_CLOCK_IOCON);

  // CLKOUT pin.
  Chip_IOCON_PinMux(LPC_IOCON, 0, 21,
                    (IOCON_MODE_INACT |
                     IOCON_DIGITAL_EN |
                     IOCON_GPIO_MODE |
                     IOCON_INPFILT_ON),
                    IOCON_FUNC1);
#if 0
  // Configure standard GPIO
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO1_4,
		       IOCON_FUNC0 | IOCON_HYS_EN | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO1_8,
		       IOCON_FUNC0 | IOCON_HYS_EN | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO1_9,
		       IOCON_FUNC0 | IOCON_HYS_EN | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO2_0,
		       IOCON_FUNC0 | IOCON_HYS_EN | IOCON_DIGMODE_EN);

  // Configure column select pins (I2C pins P0_4 and P0_5 by default set to
  // open-drain mode).
  Chip_IOCON_PinMuxSet(LPC_IOCON,
  		       IOCON_PIO0_3,
  		       IOCON_FUNC0);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO0_6,
		       IOCON_FUNC0);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO0_7,
		       IOCON_FUNC0);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO0_11,
		       IOCON_FUNC1 | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO1_0,
		       IOCON_FUNC1 | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON,
		       IOCON_PIO1_5,
		       IOCON_FUNC0);

  // Configure PWMs.
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_8, IOCON_FUNC2);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_9, IOCON_FUNC2);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_1, IOCON_FUNC3 | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_2, IOCON_FUNC3 | IOCON_DIGMODE_EN);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, IOCON_FUNC2);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, IOCON_FUNC2);

  // Configure ADC.
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_10, IOCON_FUNC1);
  Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_11, IOCON_FUNC1);
#endif
}

PinMux::~PinMux() { }

} // namespace mcu
