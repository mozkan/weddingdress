/**
 * @file Display.cpp
 *
 * @details Contains the implementation of the Display class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "Display.h"

#include "fault.h"


namespace hal {

namespace {

void WriteLEDToStringBuffer(const APA102Pixel& pixel,
                            int buffer_offset,
                            std::vector<uint8_t>& string_buffer);

}

//
// Public Function Definitions
//

Display::Display(mcu::SPIMaster& group1_spi,
                 mcu::SPIMaster& group2_spi,
                 mcu::GPIOPin&   string1_cs,
                 mcu::GPIOPin&   string2_cs,
                 mcu::GPIOPin&   string3_cs,
                 mcu::GPIOPin&   string4_cs,
                 mcu::GPIOPin&   string5_cs,
                 mcu::GPIOPin&   string6_cs,
                 mcu::GPIOPin&   enable)
  : enable_(enable),
    strings_{{
      { group1_spi, string1_cs },
      { group1_spi, string2_cs },
      { group1_spi, string3_cs },
      { group2_spi, string4_cs },
      { group2_spi, string5_cs },
      { group2_spi, string6_cs },
    }},
    frame_buffer_{{
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
      { std::vector<uint8_t>(4 * kLEDsPerString, 0), kLEDsPerString },
    }} {
  for (auto& string : strings_) {
    string.cs.Clear();
  } 
  Enable();
}

Display::~Display() {
  Disable();
}

void Display::Update(const std::vector<APA102Pixel>& string_data) {
  CopyToFrameBuffer(string_data);
  WriteFrame();
}

void Display::Update(const std::array<std::vector<APA102Pixel>,
                                      kNumberOfStrings>& string_data) {
  CopyToFrameBuffer(string_data);
  WriteFrame();
}

void Display::Enable() {
  enable_.Set();
}

void Display::Disable() {
  enable_.Clear();
}

//
// Private Function Definitions
//

void Display::CopyToFrameBuffer(const std::vector<APA102Pixel>& string_data) {
  int led_count = static_cast<int>(string_data.size());
  if (led_count > kTotalLEDs) {
    led_count = kTotalLEDs;
  }

  for (int led = 0; led < led_count; led++) {
    PlaceLEDFromContinuousString(led, string_data[led]);
  }
}

void Display::CopyToFrameBuffer(
    const std::array<std::vector<APA102Pixel>, kNumberOfStrings>& string_data) {
  for (int string = 0;
       string < static_cast<int>(frame_buffer_.size());
       string++) {
    PlaceStringSegment(string, string_data[string]);
  }
}

void Display::WriteFrame(void) {
  for (unsigned int string = 0; string < strings_.size(); string++) {
    strings_[string].cs.Set();
    strings_[string].spi.Write(frame_buffer_[string].raw_led_bytes);
    strings_[string].cs.Clear();
    
    // Crude blocking delay. TODO: Set up SPI delays in peripheral config. Need
    // this to ensure appropriate deadband between switching chip selects.
    for (int i = 0; i < 100; i++) { }
  }
}

// This method works on the assumption that all LED strings have the same number
// of LEDs.
void Display::PlaceLEDFromContinuousString(int position,
                                           const APA102Pixel& led) {
  int string = position / kLEDsPerString;
  int start_offset = (position % kLEDsPerString) * 4;

  ASSERT(string < kNumberOfStrings);

  WriteLEDToStringBuffer(led,
                         start_offset,
                         frame_buffer_[string].raw_led_bytes);
  //frame_buffer_[string].raw_led_bytes[start_offset]     = led.bright();
  //frame_buffer_[string].raw_led_bytes[start_offset + 1] = led.b();
  //frame_buffer_[string].raw_led_bytes[start_offset + 2] = led.g();
  //frame_buffer_[string].raw_led_bytes[start_offset + 3] = led.r();
}

void Display::PlaceStringSegment(int string,
                                 const std::vector<APA102Pixel>& string_data) {
  int led_count = static_cast<int>(string_data.size());
  int frame_buffer_led_count = frame_buffer_[string].string_size;

  if (led_count > frame_buffer_led_count) {
    led_count = frame_buffer_led_count;
  }

  int offset = 0;
  for (int led = 0; led < led_count; led++) {
    //frame_buffer_[string].raw_led_bytes[offset]     = string_data[led].bright();
    //frame_buffer_[string].raw_led_bytes[offset + 1] = string_data[led].b();
    //frame_buffer_[string].raw_led_bytes[offset + 2] = string_data[led].g();
    //frame_buffer_[string].raw_led_bytes[offset + 3] = string_data[led].r();
    WriteLEDToStringBuffer(string_data[led],
                           offset,
                           frame_buffer_[string].raw_led_bytes);
    offset += 4;
  }
}

namespace {

void WriteLEDToStringBuffer(const APA102Pixel& pixel,
                            int buffer_offset,
                            std::vector<uint8_t>& string_buffer) {
  string_buffer[buffer_offset]     = 0xE0 | pixel.bright();
  string_buffer[buffer_offset + 1] = pixel.b();
  string_buffer[buffer_offset + 2] = pixel.g();
  string_buffer[buffer_offset + 3] = pixel.r();
}

}

} // namespace hal
