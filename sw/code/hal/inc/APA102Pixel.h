#ifndef APA102PIXEL_H_
#define APA102PIXEL_H_

/**
 * @file APA102Pixel.h
 *
 * @details Contains the declaration of the APA102Pixel class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include <cstdint>


namespace hal {

//
// APA102Pixel Class Declaration
//

/**
 * Class to manage raw color data and color manipulation for a single LED. This
 * class, specifically, represents a single APA102 RGB LED. It does not
 * implement communication with APA102 LEDs.
 */
class APA102Pixel
{
 public:
  static constexpr uint8_t kMaximumBrightness = 31;
  static constexpr uint8_t kDefaultGlobalBrightness = kMaximumBrightness;

  /**
   * Constructor for the APA102Pixel class. Initializes R, G, B, and global
   * brightness values to zero.
   */
  APA102Pixel();

  /**
   * Constructor for the APA102Pixel class. Initializes R, G, and B values to a
   * user provided value. Initializes global brightness to
   * kDefaultGlobalBrightness.
   */
  APA102Pixel(uint8_t r, uint8_t g, uint8_t b);

  /**
   * Constructor for the APA102Pixel class. Initializes R, G, B, and global
   * brightness to user provided values.
   */
  APA102Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t bright);

  ~APA102Pixel();

  void set_r(uint8_t r) { r_ = r; }
  void set_g(uint8_t g) { g_ = g; }
  void set_b(uint8_t b) { b_ = b; }
  void set_bright(uint8_t bright) { bright_ = bright; }

  uint8_t r(void) const { return r_; }
  uint8_t g(void) const { return g_; }
  uint8_t b(void) const { return b_; }
  uint8_t bright(void) const { return bright_; }

  /**
   * (NOT TESTED)
   * Gets the four-byte raw packed representation for shifting out to the LED
   * string.
   *
   * Note: This may be useful for when DMA based SPI transfers are implemented.
   *
   * @return Raw representation of LED data to send over the wire.
   */
  uint32_t GetRaw(void) {
    return (static_cast<uint32_t>(bright_ | 0xE0) << 24) |
           (static_cast<uint32_t>(b_) << 16) |
           (static_cast<uint32_t>(g_) << 8) |
           static_cast<uint32_t>(r_);
  }

 private:
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;
  uint8_t bright_;
};

} // namespace hal

#endif /* APA102PIXEL_H_ */
