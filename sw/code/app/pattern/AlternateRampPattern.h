#ifndef ALTERNATE_RAMP_PATTERN_H_
#define ALTERNATE_RAMP_PATTERN_H_

/**
 * @file AlternateRampPattern.h
 *
 * @details Header file for the declaration of the AlternateRampPattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <array>

#include "Display.h"

#include "Pattern.h"


namespace app {
namespace pattern {

//
// AlternateRampPattern Class Declaration
//

/**
 * Generates a pattern that ramps up even pixels while ramping down odd pixels.
 * Once the limit is reached, the ramp directions change. Does this with white
 * color only right now.
 */
class AlternateRampPattern : public Pattern {
 public:
  /**
   * Constructor for the AlternateRampPattern class.
   *
   */
  AlternateRampPattern(hal::Display& display);

  virtual ~AlternateRampPattern();

  // Disallow copy and assign.
  AlternateRampPattern(const AlternateRampPattern&) = delete;
  AlternateRampPattern& operator=(const AlternateRampPattern&) = delete;

 private:
  static const uint8_t kMinBrightness = 32;
  static const uint8_t kMaxBrightness = 255;

  virtual void CalculateNextIteration(void);
  void UpdateEveryOtherLED(int start_led, uint8_t value);

  int8_t  direction_even_;
  int8_t  direction_odd_;
  uint8_t even_led_value_;
  uint8_t odd_led_value_;
};

} // namespace pattern
} // namespace app

#endif /* ALTERNATE_RAMP_PATTERN_H_ */
