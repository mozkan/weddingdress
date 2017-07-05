/**
 * @file ADCChannel.cpp
 *
 * @details Contains the implementation of the ADCChannel class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "ADCChannel.h"


namespace mcu {

namespace {

//
// Constants
//

// To be indexed by mcu::ADCChannels
#if 0
const ADC_CHANNEL_T kADCChannels[2] = {
  ADC_CH6, //mcu::ADCChannels::AD6
  ADC_CH7  //mcu::ADCChannels::AD7
};
#endif

}


//
// ADCChannel Class Definition
//

ADCChannel::ADCChannel(ADCChannels /*channel*/)
#if 0
  : adc_channel_(channel),
    adc_(LPC_ADC),
    lpc_open_channel_(kADCChannels[static_cast<int>(channel)])
#endif
{
  //...
}

ADCChannel::~ADCChannel() { }

uint16_t ADCChannel::Read(void)
{
#if 0
  Chip_ADC_EnableChannel(adc_, lpc_open_channel_, ENABLE);

  // Temporary hack - blocking delay to wait until conversion is done.
  for (uint32_t i = 0; i < 1000; i++) { }

  Chip_ADC_SetStartMode(adc_, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

  while (Chip_ADC_ReadStatus(adc_,
			     lpc_open_channel_,
			     ADC_DR_DONE_STAT) != SET) { }

  uint16_t result;
  Chip_ADC_ReadValue(adc_, lpc_open_channel_, &result);

  // Disable the channel. Only one channel can be enabled at any given time.
  Chip_ADC_EnableChannel(adc_, lpc_open_channel_, DISABLE);

  return result;
#else
  return 0;
#endif
}

} // namespace mcu
