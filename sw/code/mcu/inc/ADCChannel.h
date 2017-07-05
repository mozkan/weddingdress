#ifndef ADCCHANNEL_H_
#define ADCCHANNEL_H_

/**
 * @file ADCChannel.h
 *
 * @details Contains the declaration of the ADCChannel class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include "MCUConfig.h"


namespace mcu {

//
// ADCChannel Class Declaration
//

/**
 * Driver class encapsulating a single ADC channel.
 */
class ADCChannel {
 public:
  static const uint16_t kBitDepth  = 12;
  static const uint16_t kFullScale = 4096;

  /**
   * Constructor for the ADCChannel class.
   *
   * @param[in] channel The ADC channel to control.
   */
  ADCChannel(ADCChannels channel);

  ~ADCChannel();

  /**
   * Reads a value from the ADC. Blocks until the conversion is done.
   *
   * @return The ADC reading as a number between 0 and kFullScale.
   */
  uint16_t Read(void);

  // Disallow copy and assign.
  ADCChannel(const ADCChannel&) = delete;
  ADCChannel& operator=(const ADCChannel&) = delete;

 private:
#if 0
  ADCChannels   adc_channel_;
  LPC_ADC_T*    adc_;
  ADC_CHANNEL_T lpc_open_channel_;
#endif
};

} // namespace mcu

#endif /* ADCCHANNEL_H_ */
