#include <cstdint>

#include <vector>

#include "chip.h"

#include "fault.h"

#include "MCU.h"
#include "MCUConfig.h"

int main(void) {
  mcu::MCU mcu;

  // LEDs.
  mcu::GPIOPin& green_led1 = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_14);
  mcu::GPIOPin& green_led2 = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_15);

  // LED string testing.
  mcu::GPIOPin& led_power_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_2);
  mcu::GPIOPin& led_string1_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_23);
  mcu::GPIOPin& led_string2_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_24);
  mcu::GPIOPin& led_string3_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_25);
  mcu::GPIOPin& led_string4_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_11);
  mcu::GPIOPin& led_string5_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_12);
  mcu::GPIOPin& led_string6_enable = mcu.GetGPIOPin(mcu::GPIOPins::kPIO0_13);

  mcu::SPIMaster& spi0 = mcu.GetSPIMaster(mcu::SPIPeripherals::kSPI0);
  mcu::SPIMaster& spi1 = mcu.GetSPIMaster(mcu::SPIPeripherals::kSPI1);

  led_power_enable.Set();
  led_string6_enable.Set();

  std::vector<uint8_t> spi_write = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  while(1) {
    /*
    green_led1.Set();
    green_led2.Clear();

    led_string1_enable.Set();
    led_string2_enable.Set();
    led_string3_enable.Set();
    led_string4_enable.Set();
    led_string5_enable.Set();
    led_string6_enable.Set();

    for (int i = 0; i < 600000; i++) {}

    green_led1.Clear();
    green_led2.Set();

    led_string1_enable.Clear();
    led_string2_enable.Clear();
    led_string3_enable.Clear();
    led_string4_enable.Clear();
    led_string5_enable.Clear();
    led_string6_enable.Clear();

    for (int i = 0; i < 600000; i++) {}
    */

    //spi0.Write(spi_write);
    spi1.Write(spi_write);
  }

  return 0;
}
