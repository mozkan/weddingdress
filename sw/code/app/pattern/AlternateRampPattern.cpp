/**
 * @file AlternateRampPattern.cpp
 *
 * @details Contains the implementation of the AlternateRampPattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "AlternateRampPattern.h"

#include "Display.h"

#include "PatternHelpers.h"


namespace app {
namespace pattern {

//
// Task Class Definition
//

AlternateRampPattern::AlternateRampPattern(hal::Display& display) 
  : Pattern(display),
    direction_even_(1),
    direction_odd_(-1),
    even_led_value_(kMinBrightness),
    odd_led_value_(kMaxBrightness) { }

AlternateRampPattern::~AlternateRampPattern() { }


//
// Private Member Definitions
//

void AlternateRampPattern::CalculateNextIteration(void) {
  if (even_led_value_ >= kMaxBrightness) {
    direction_even_ = -1;
    direction_odd_ = 1;
  } else if (even_led_value_ <= kMinBrightness) {
    direction_even_ = 1;
    direction_odd_ = -1;
  }

  even_led_value_ = Add8Sat(even_led_value_, direction_even_);
  odd_led_value_  = Add8Sat(odd_led_value_, direction_odd_);

  // Set even LEDs.
  UpdateEveryOtherLED(0, even_led_value_);

  // Set odd LEDs.
  UpdateEveryOtherLED(1, odd_led_value_);
}

void AlternateRampPattern::UpdateEveryOtherLED(int start_led, uint8_t value) {
  for (auto& string : buffer_) {
    for (int led = start_led; led < hal::Display::kLEDsPerString; led += 2) {
      string[led].set_r(value);
      string[led].set_g(value);
      string[led].set_b(value);
    }
  }
}

} // namespace pattern
} // namespace app
