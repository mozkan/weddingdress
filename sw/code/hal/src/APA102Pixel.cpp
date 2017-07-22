/**
 * @file APA102Pixel.cpp
 *
 * @details Contains the implementation of the APA102Pixel class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "APA102Pixel.h"


namespace hal {

//
// APA102Pixel Class Definition
//

APA102Pixel::APA102Pixel() : r_(0), g_(0), b_(0), bright_(0) { }

APA102Pixel::APA102Pixel(uint8_t r, uint8_t g, uint8_t b)
  : r_(r), g_(g), b_(b), bright_(kMaximumBrightness) { }

APA102Pixel::APA102Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t bright)
  : r_(r), g_(g), b_(b), bright_(bright) { }

APA102Pixel::~APA102Pixel() { }

} // namespace hal
