#ifndef DISPLAY_H_
#define DISPLAY_H_

/**
 * @file Display.h
 *
 * @details Contains the declaration of the Display class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include <cstdint>

#include <array>
#include <vector>

#include "GPIOPin.h"
#include "SPIMaster.h"

#include "APA102Pixel.h"


namespace hal {

//
// Display Class Declaration
//

/**
 * Driver class for driving the LED array on the Wedfestdress.
 */
class Display
{
 public:
  static constexpr int kLEDsPerString = 25;
  static constexpr int kNumberOfStrings = 6;
  static constexpr int kTotalLEDs = kLEDsPerString * kNumberOfStrings;

  typedef std::array<std::vector<APA102Pixel>, kNumberOfStrings> DisplayBuffer;

  /**
   * Constructor for the Display class.
   *
   * @param[in] group1_spi The SPI master port for writing pixel data out to
   *     strings 1 to 3.
   * @param[in] group2_spi The SPI master port for writing pixel data out to
   *     strings 4 to 6.
   * @param[in] string[1..6]_cs The chip select GPIOs for enabling communication
   *     to strings 1 to 6.
   */
  Display(mcu::SPIMaster& group1_spi,
          mcu::SPIMaster& group2_spi,
          mcu::GPIOPin&   string1_cs,
          mcu::GPIOPin&   string2_cs,
          mcu::GPIOPin&   string3_cs,
          mcu::GPIOPin&   string4_cs,
          mcu::GPIOPin&   string5_cs,
          mcu::GPIOPin&   string6_cs,
          mcu::GPIOPin&   enable);

  ~Display();

  /**
   * Writes out a new set of pixel data to the LED strings as a continuous
   * block. Blocks until all data has been written.
   *
   * @param[in] string_data A continuous set of LED data for all LEDs in the
   *     system.
   * @return Nothing.
   */
  void Update(const std::vector<APA102Pixel>& string_data);

  /**
   * Writes out a new set of pixel data to the LED strings as a separate set of
   * strings. Blocks until all data has been written.
   *
   * @param[in] string_data An array of LED string data. One vector per LED
   *     string, stored in an array of size kNumberOfStrings.
   * @return Nothing.
   */
  //void Update(const std::array<std::vector<APA102Pixel>,
  //                             kNumberOfStrings>& string_data);
  void Update(const DisplayBuffer& string_data);

  /**
   * Enables power to the pixel array.
   */
  void Enable(void);

  /**
   * Disables power to the pixel array.
   */
  void Disable(void);

  // Disallow copy and assign.
  Display(const Display&) = delete;
  Display& operator=(const Display&) = delete;

 private:
  struct StringConfig {
    mcu::SPIMaster& spi;
    mcu::GPIOPin&   cs;
  };

  struct StringBuffer {
    std::vector<uint8_t> raw_led_bytes;
    const int            string_size;
  };

  void CopyToFrameBuffer(const std::vector<APA102Pixel>& string_data);
  void CopyToFrameBuffer(const std::array<std::vector<APA102Pixel>,
                                          kNumberOfStrings>& string_data);
  void WriteFrame(void);
  void PlaceLEDFromContinuousString(int position, const APA102Pixel& led);
  void PlaceStringSegment(int string,
                          const std::vector<APA102Pixel>& string_data);

  mcu::GPIOPin& enable_;
  const std::array<StringConfig, kNumberOfStrings> strings_;
  std::array<StringBuffer, kNumberOfStrings> frame_buffer_;
};

} // namespace hal

#endif /* DISPLAY_H_ */
