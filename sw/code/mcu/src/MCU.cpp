/**
 * @file MCU.cpp
 *
 * @details Implementation of the MCU class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "chip.h"

#include "fault.h"

#include "MCU.h"


//
// LPCOpen Config
//

const uint32_t ExtClockIn = 0;


namespace mcu {

//
// MCU Class Definition
//

bool MCU::initialized_ = false;

MCU::MCU()
  : clocking_(kCPUClockHz),
    pinmux_(),
    gpio_0_2_(GPIOPins::kPIO0_2, GPIOPin::GPIODirection::Output),
    gpio_0_11_(GPIOPins::kPIO0_11, GPIOPin::GPIODirection::Output),
    gpio_0_12_(GPIOPins::kPIO0_12, GPIOPin::GPIODirection::Output),
    gpio_0_13_(GPIOPins::kPIO0_13, GPIOPin::GPIODirection::Output),
    gpio_0_14_(GPIOPins::kPIO0_14, GPIOPin::GPIODirection::Output),
    gpio_0_15_(GPIOPins::kPIO0_15, GPIOPin::GPIODirection::Output),
    gpio_0_18_(GPIOPins::kPIO0_18, GPIOPin::GPIODirection::Output),
    gpio_0_19_(GPIOPins::kPIO0_19, GPIOPin::GPIODirection::Input),
    gpio_0_23_(GPIOPins::kPIO0_23, GPIOPin::GPIODirection::Output),
    gpio_0_24_(GPIOPins::kPIO0_24, GPIOPin::GPIODirection::Output),
    gpio_0_25_(GPIOPins::kPIO0_25, GPIOPin::GPIODirection::Output),
    gpio_1_17_(GPIOPins::kPIO1_17, GPIOPin::GPIODirection::Input),
    spi0_(SPIPeripherals::kSPI0, SPIMaster::Mode::kSPIMode3, 1000000),
    spi1_(SPIPeripherals::kSPI1, SPIMaster::Mode::kSPIMode3, 1000000),
#if 0
    pwm_ct16b0_m0_(PWMChannels::kCT16B0Mat0),
    pwm_ct16b0_m1_(PWMChannels::kCT16B0Mat1),
    pwm_ct32b0_m0_(PWMChannels::kCT32B0Mat0),
    pwm_ct32b0_m1_(PWMChannels::kCT32B0Mat1),
    pwm_ct32b1_m0_(PWMChannels::kCT32B1Mat0),
    pwm_ct32b1_m1_(PWMChannels::kCT32B1Mat1),
    timer_ct16b1_(TimerChannels::kCT16B1),
    ad6_(ADCChannels::kAD6),
    ad7_(ADCChannels::kAD7),
#endif
    gpio_pins_()
#if 0
    pwms_(),
#endif
{
  ASSERT(initialized_ == false);
  initialized_ = true;

  PopulateGPIOLookup();
#if 0
  PopulateADCChannelLookup();
#endif

  // Set clock signal on CLKOUT pin.
  SetCLKOUT();
}

MCU::~MCU() {
}

GPIOPin& MCU::GetGPIOPin(GPIOPins gpio_pin) {
  auto pin = gpio_pins_.find(gpio_pin);
  ASSERT(pin != gpio_pins_.end());

  return *(pin->second);
}

SPIMaster& MCU::GetSPIMaster(SPIPeripherals spi_port) {
  if (spi_port == SPIPeripherals::kSPI0) {
    return spi0_;
  } else if (spi_port == SPIPeripherals::kSPI1) {
    return spi1_;
  } else {
    ASSERT(false);
  }
}

#if 0
PWM16& MCU::GetPWMChannel(PWMChannels channel) {
  return *(pwms_[static_cast<int>(channel)]);
}

Timer& MCU::GetTimerChannel(TimerChannels channel) {
  assert(channel == TimerChannels::kCT16B1);

  return timer_ct16b1_;
}

ADCChannel& MCU::GetADCChannel(ADCChannels channel) {
  switch (channel) {
    case ADCChannels::kAD6:
      return ad6_;
    break;

    case ADCChannels::kAD7:
      return ad7_;
    break;

    default:
      ASSERT(false);
    break;
  }
}
#endif


//
// Private Functions
//

void MCU::SetCLKOUT(void) {
  Chip_Clock_SetCLKOUTSource(SYSCON_CLKOUTSRC_MAINCLK, 99);
}

void MCU::PopulateGPIOLookup(void) {
  // Add pins to table.
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_2, &gpio_0_2_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_11, &gpio_0_11_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_12, &gpio_0_12_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_13, &gpio_0_13_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_14, &gpio_0_14_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_15, &gpio_0_15_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_18, &gpio_0_18_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_19, &gpio_0_19_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_23, &gpio_0_23_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_24, &gpio_0_24_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO0_25, &gpio_0_25_));
  gpio_pins_.insert(
      std::pair<GPIOPins, GPIOPin*>(GPIOPins::kPIO1_17, &gpio_1_17_));
}

#if 0
void MCU::ConfigureADC(void) {
  ADC_CLOCK_SETUP_T adc_setup = { ADC_MAX_SAMPLE_RATE, ADC_10BITS, false };
  Chip_ADC_Init(LPC_ADC, &adc_setup);
}
#endif

} // namespace mcu
