#if 0
#ifndef SPIPORT_H_
#define SPIPORT_H_

/**
 * @file SPIPort.h
 *
 * @details Header file for the declaration of the SPI peripheral driver class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include <vector>

#include "MCUConfig.h"


namespace mcu {

//
// SPIPort Class Declaration
//

/**
 * A SPI port peripheral.
 */
class SPIPort {
 public:
  enum class Mode {
    kSPIMode0 = 0, //! Polarity = 0, Phase = 0.
    kSPIMode1,     //! Polarity = 0, Phase = 1.
    kSPIMode2,     //! Polarity = 1, Phase = 0.
    kSPIMode3      //! Polarity = 1, Phase = 1.
  };

  /**
   * Constructor for the SPIPort class. Configures peripheral functions.
   *
   * @param[in] port The SPI port on this MCU.
   */
  SPIPort(SPIPeripherals port, Mode mode);

  ~SPIPort();

  /**
   * Writes bytes to a SPI port.
   *
   * @param[in] buffer The byte buffer to write.
   *
   * @return Nothing.
   */
  void Write(std::vector<uint8_t> buffer);

  // Disallow copy and assign.
  SPIPort(const SPIPort&) = delete;
  SPIPort& operator=(const SPIPort&) = delete;

 private:
  uint8_t port_;
};

} // namespace mcu

#endif /* SPIPORT_H_ */
#endif
