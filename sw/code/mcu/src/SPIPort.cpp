/**
 * @file SPIPort.cpp
 *
 * @details Contains the implementation of the SPI peripheral driver class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */
#if 0
#include <cstdint>

#include "chip.h"

#include "SPIPort.h"


namespace mcu {

//
// Type Declarations
//

namespace {

struct ResourceMapping {
  uint8_t port_reg;
  uint8_t port_bit;
};

}


//
// Constants
//

namespace {

const Info kGPIOs[12] = {
  { 0, 2 },  // kPIO0_2
  { 0, 11 }, // kPIO0_11
  { 0, 12 }, // kPIO0_12
  { 0, 13 }, // kPIO0_13
  { 0, 14 }, // kPIO0_14
  { 0, 15 }, // kPIO0_15
  { 0, 18 }, // kPIO0_18
  { 0, 19 }, // kPIO0_19
  { 0, 23 }, // kPIO0_23
  { 0, 24 }, // kPIO0_24
  { 0, 25 }, // kPIO0_25
  { 1, 17 }, // kPIO1_17
};

}


//
// GPIOPin Class Definition
//

GPIOPin::GPIOPin(GPIOPins pin, GPIODirection direction)
  :  port_(kGPIOs[static_cast<int>(pin)].port_reg),
     bit_(kGPIOs[static_cast<int>(pin)].port_bit) {
  SetDirection(direction);
}

GPIOPin::~GPIOPin() { }

void GPIOPin::Set(void) {
  Chip_GPIO_SetPinState(LPC_GPIO, port_, bit_, true);
}

void GPIOPin::Clear(void) {
  Chip_GPIO_SetPinState(LPC_GPIO, port_, bit_, false);
}

void GPIOPin::SetOutput(GPIOValue value) {
  if (value == GPIOValue::High) {
    Set();
  } else {
    Clear();
  }
}

GPIOPin::GPIOValue GPIOPin::ReadInput(void) {
  if (Chip_GPIO_GetPinState(LPC_GPIO, port_, bit_)) {
    return GPIOPin::GPIOValue::High;
  } else {
    return GPIOValue::Low;
  }
}

void GPIOPin::SetDirection(GPIOPin::GPIODirection direction) {
  if (direction == GPIOPin::GPIODirection::Output) {
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, port_, bit_);
  } else {
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, port_, bit_);
  }
}

} // namespace mcu
#endif
