/**
 * @file FlashyDinglerPattern.cpp
 *
 * @details Contains the implementation of the FlashyDinglerPattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "FlashyDinglerPattern.h"

#include <cstdlib>

#include "fault.h"

#include "Display.h"

#include "PatternHelpers.h"


namespace app {
namespace pattern {

namespace {

void UpdateFadeBalanced(uint8_t  brightness,
                        int8_t*  rate,
                        uint8_t* lim_high,
                        uint8_t* lim_low);
void UpdateFadeDownwards(uint8_t  brightness,
                         int8_t*  rate,
                         uint8_t* lim_high,
                         uint8_t* lim_low);
void SetNewLimits(uint8_t* lim_high, uint8_t* lim_low);

constexpr uint8_t kRampStartBrightness = 20;
constexpr uint8_t kMaxBrightness       = 255;
constexpr uint8_t kMaxRampRate         = 10;
constexpr uint8_t kMaxLimitDistance    = kMaxBrightness / 2;
constexpr uint8_t kTwinkleMidpoint     = kMaxBrightness / 2;

} // namespace

//
// Task Class Definition
//

FlashyDinglerPattern::FlashyDinglerPattern(hal::Display& display) 
  : Pattern(display),
    state_(static_cast<int>(kRampUp)),
    pattern_data_{{
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
      std::vector<LEDAttributes>(hal::Display::kLEDsPerString, {0, 0, 0}),
    }} {
  srand(1234);
  Reset();

  ASSERT(pattern_data_.size() == buffer_.size());
  for (int string = 0;
       string < static_cast<int>(pattern_data_.size());
       string++) {
    ASSERT(pattern_data_[string].size() == buffer_[string].size());
  }
}

FlashyDinglerPattern::~FlashyDinglerPattern() { }

void FlashyDinglerPattern::Reset(void) {
  Pattern::Reset();
  state_ = State::kRampUp;

  for (auto& string : pattern_data_) {
    for (auto& led : string) {
      led.r = kRampStartBrightness;
      led.g = kRampStartBrightness;
      led.b = kRampStartBrightness;
      led.r_rate = -1;
      led.g_rate = -1;
      led.b_rate = -1;
      led.r_lim_high = kMaxBrightness;
      led.g_lim_high = kMaxBrightness;
      led.b_lim_high = kMaxBrightness;
      led.r_lim_low = kMaxBrightness;
      led.g_lim_low = kMaxBrightness;
      led.b_lim_low = kMaxBrightness;
    }
  }
}


//
// Private Member Definitions
//

void FlashyDinglerPattern::CalculateNextIteration(void) {
  //int rnum = rand() % 100;
  switch (state_) {
    case kRampUp:
      StateRampUp();
    break;

    case kRampDown:
      StateRampDown();
    break;

    case kTwinkle:
      StateRampTwinkle();
    break;
  }
}

void FlashyDinglerPattern::NextState(void) {
  state_++;
  if (state_ == kStateCount) {
    state_ = 0;
  }
}

void FlashyDinglerPattern::StateRampUp(void) {
  for (auto& string : pattern_data_) {
    for (auto& led : string) {
      led.r++;
      led.g++;
      led.b++;
    }
  }

  TransferLEDData();

  if (pattern_data_[0][0].r == kMaxBrightness) {
    NextState();
    NextState(); // DEBUG
  }
}

void FlashyDinglerPattern::StateRampDown(void) {
  bool all_leds_dim = true;

  for (auto& string : pattern_data_) {
    for (auto& led : string) {
      Twinkle(led, true);

      if ((led.r > 0) || (led.g > 0) || (led.b > 0)) {
        all_leds_dim = false;
      }
    }
  }

  TransferLEDData();

  if (all_leds_dim) {
    NextState();
  }
}

void FlashyDinglerPattern::StateRampTwinkle(void) {
  for (auto& string : pattern_data_) {
    for (auto& led : string) {
      Twinkle(led, false);
    }
  }

  TransferLEDData();
}

void FlashyDinglerPattern::TransferLEDData(void) {
  for (int string = 0;
       string < static_cast<int>(pattern_data_.size());
       string++) {
    for (int led = 0;
         led < static_cast<int>(pattern_data_[string].size());
         led++) {
      buffer_[string][led].set_r(pattern_data_[string][led].r);
      buffer_[string][led].set_g(pattern_data_[string][led].g);
      buffer_[string][led].set_b(pattern_data_[string][led].b);
    }
  }
}

void FlashyDinglerPattern::Twinkle(LEDAttributes& led, bool ramp_down_only) {
  led.r = Add8Sat(led.r, led.r_rate);
  led.g = Add8Sat(led.g, led.g_rate);
  led.b = Add8Sat(led.b, led.b_rate);

  if (ramp_down_only) {
    UpdateFadeDownwards(led.r, &led.r_rate, &led.r_lim_high, &led.r_lim_low);
    UpdateFadeDownwards(led.g, &led.g_rate, &led.g_lim_high, &led.g_lim_low);
    UpdateFadeDownwards(led.b, &led.b_rate, &led.b_lim_high, &led.b_lim_low);
  } else {
    UpdateFadeBalanced(led.r, &led.r_rate, &led.r_lim_high, &led.r_lim_low);
    UpdateFadeBalanced(led.g, &led.g_rate, &led.g_lim_high, &led.g_lim_low);
    UpdateFadeBalanced(led.b, &led.b_rate, &led.b_lim_high, &led.b_lim_low);
  }
}


namespace {

/**
 * Sets new limits for ramping a single LED color channel if necessary. If the
 * current color is below its lower limit or above its upper limit, new bounds
 * are found and a new rate is chosen that ramps in the opposite direction.
 * For this balanced version, the rate can swing in both directions.
 *
 * @param[in] brightness The current value of the LED color channel to adjust.
 * @param[inout] rate The current rate to adjust if necessary.
 * @param[inout] lim_high The current high bound on brightness to adjust if
 *     necessary.
 * @param[inout] lim_low The current high bound on brightness to adjust if
 *     necessary.
 */
void UpdateFadeBalanced(uint8_t  brightness,
                        int8_t*  rate,
                        uint8_t* lim_high,
                        uint8_t* lim_low) {
  if (brightness <= *lim_low) {
    // Need to ramp up now. Set a positive rate.
    *rate = static_cast<int8_t>(rand() % kMaxRampRate + 1);
    SetNewLimits(lim_high, lim_low);
  } else if (brightness >= *lim_high) {
    // Need to ramp down now. Set a negative rate.
    *rate = (-1) * static_cast<int8_t>(rand() % kMaxRampRate + 1);
    SetNewLimits(lim_high, lim_low);
  }
}

/**
 * Like the GetNewLimitsBalanced function, except the rate and new bounds always
 * result in a brightness that decreases.
 *
 * @see UpdateFadeBalanced.
 */
void UpdateFadeDownwards(uint8_t  brightness,
                         int8_t*  rate,
                         uint8_t* lim_high,
                         uint8_t* lim_low) {
  // Always ramp down.
  if (brightness <= *lim_low) {
    *rate = (-1) * static_cast<int8_t>(rand() % kMaxRampRate + 1);
    *lim_low = Sub8Sat(*lim_low,
                       static_cast<uint8_t>(rand() % kMaxLimitDistance));
  }
}

void SetNewLimits(uint8_t* lim_high, uint8_t* lim_low) {
  *lim_low = Sub8Sat(kTwinkleMidpoint,
                     static_cast<uint8_t>(rand() % kMaxLimitDistance));
  *lim_high = Add8Sat(kTwinkleMidpoint,
                      static_cast<uint8_t>(rand() % kMaxLimitDistance));
}

} // namespace

} // namespace pattern
} // namespace app
