#ifndef SPIMASTER_H_
#define SPIPMASTER_H_

/**
 * @file SPIMaster.h
 *
 * @details Header file for the declaration of the SPI master peripheral driver
 * class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>

#include <vector>

#include "chip.h"

#include "MCUConfig.h"


namespace mcu {

//
// SPIMaster Class Declaration
//

/**
 * A SPI master peripheral. In addition to the configuration options in the
 * constructor, the peripheral is configured for LSB first operation.
 */
class SPIMaster {
 public:
  enum class Mode {
    kSPIMode0 = 0, //! Polarity = 0, Phase = 0.
    kSPIMode1,     //! Polarity = 0, Phase = 1.
    kSPIMode2,     //! Polarity = 1, Phase = 0.
    kSPIMode3      //! Polarity = 1, Phase = 1.
  };

  /**
   * Constructor for the SPIMaster class. Configures peripheral functions.
   *
   * @param[in] port The SPI port on this MCU.
   * @param[in] mode The SPI mode that sets CPOL and CPHA.
   * @param[in] frequency_hz The frequency in Hz of the SPI clock.
   */
  SPIMaster(SPIPeripherals port, Mode mode, uint32_t frequency_hz);

  ~SPIMaster();

  /**
   * Writes bytes to a SPI port.
   *
   * @param[in] buffer The byte buffer to write.
   *
   * @return Nothing.
   */
  void Write(const std::vector<uint8_t>& buffer);

  // Disallow copy and assign.
  SPIMaster(const SPIMaster&) = delete;
  SPIMaster& operator=(const SPIMaster&) = delete;

 private:
 static constexpr int kFIFOSize = 8;

 LPC_SPI_T*  peripheral_;
 SPIM_XFER_T transfer_;
 uint16_t    tx_buffer_[kFIFOSize];
 uint16_t    rx_buffer_[kFIFOSize];
};

} // namespace mcu

#endif /* SPIMASTER_H_ */
