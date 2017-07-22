/**
 * @file SPIMaster.cpp
 *
 * @details Contains the implementation of the SPI peripheral driver class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "SPIMaster.h"

#include "LPCOpenCfg.h"

namespace mcu {

//
// Constants
//

namespace {

LPC_SPI_T* kSPIPeripherals[2] = {
  LPC_SPI0,
  LPC_SPI1
};

SPI_CLOCK_MODE_T kLPCModes[4] = {
  SPI_CLOCK_CPHA0_CPOL0, // kSPIMode0
  SPI_CLOCK_CPHA1_CPOL0, // kSPIMode1
  SPI_CLOCK_CPHA0_CPOL1, // kSPIMode2
  SPI_CLOCK_CPHA1_CPOL1  // kSPIMode3
};

}


//
// SPIMaster Class Definition
//

SPIMaster::SPIMaster(SPIPeripherals port, Mode mode, uint32_t frequency_hz)
  : peripheral_(kSPIPeripherals[static_cast<int>(port)]) {
  Chip_SPI_Enable(peripheral_);

  SPI_CFGSETUP_T spi_config;
  spi_config.master = 1;
  spi_config.lsbFirst= 0;
  spi_config.mode= kLPCModes[static_cast<int>(mode)];
  Chip_SPI_ConfigureSPI(peripheral_, &spi_config);
  
  Chip_SPIM_SetClockRate(peripheral_, frequency_hz);

  // In this crude blocking transfer mode, the FIFOs will be used to transfer
  // one byte at a time. Most of the transmit settings will be configured once
  // and not touched again for a single element transfer.
  transfer_.txData = &tx_buffer_;
  transfer_.rxData = &rx_buffer_;
  transfer_.txCount = 0;
  transfer_.rxCount = 0;
  transfer_.dataWidth = 8;
  transfer_.sselNum = 0; // Not used.
  transfer_.txIndex = 0;
  transfer_.rxIndex = 0;
}

SPIMaster::~SPIMaster() { }

void SPIMaster::Write(const std::vector<uint8_t>& buffer) {
  Chip_SPI_FlushFIFOs(peripheral_);

  int buffer_index = 0;
  const int kBytesToWrite = static_cast<int>(buffer.size());

  while (buffer_index < kBytesToWrite) {
    int byte = 0;
    while (byte < kFIFOSize) {
      tx_buffer_[byte] = buffer[buffer_index];

      byte++;
      buffer_index++;

      if (buffer_index >= kBytesToWrite) {
        break;
      }
    }

    transfer_.txCount = byte;
    Chip_SPIM_XferFIFO(peripheral_, &transfer_);
  }
}

} // namespace mcu
