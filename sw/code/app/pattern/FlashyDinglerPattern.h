#ifndef FLASHY_DINGLER_PATTERN_H_
#define FLASHY_DINGLER_PATTERN_H_

/**
 * @file FlashyDinglerPattern.h
 *
 * @details Header file for the declaration of the FlashyDinglerPattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <array>
#include <vector>

#include "Display.h"

#include "Pattern.h"


namespace app {
namespace pattern {

//
// FlashyDinglerPattern Class Declaration
//

/**
 * Generates a pattern that starts off by ramping from dim to max brightness
 * exponentially, then fading to color twinkles, where it continues to twinkle
 * for the duration of the pattern.
 */
class FlashyDinglerPattern : public Pattern {
 public:
  /**
   * Constructor for the FlashyDinglerPattern class.
   *
   */
  FlashyDinglerPattern(hal::Display& display);

  virtual ~FlashyDinglerPattern();

  void Reset(void) override;

  // Disallow copy and assign.
  FlashyDinglerPattern(const FlashyDinglerPattern&) = delete;
  FlashyDinglerPattern& operator=(const FlashyDinglerPattern&) = delete;

 private:
  enum State {
    kRampUp = 0,
    kRampDown,
    kTwinkle,
    kStateCount
  };

  struct LEDAttributes {
    uint8_t r;
    int8_t  r_rate;
    uint8_t r_lim_high;
    uint8_t r_lim_low;
    uint8_t g;
    int8_t  g_rate;
    uint8_t g_lim_high;
    uint8_t g_lim_low;
    uint8_t b;
    int8_t  b_rate;
    uint8_t b_lim_high;
    uint8_t b_lim_low;
  };

  void CalculateNextIteration(void) override;
  void NextState(void);
  void StateRampUp(void);
  void StateRampDown(void);
  void StateRampTwinkle(void);
  void TransferLEDData(void);
  void Twinkle(LEDAttributes& led, bool ramp_down_only);

  int state_;
  std::array<std::vector<LEDAttributes>,
             hal::Display::kNumberOfStrings> pattern_data_;
};

} // namespace pattern
} // namespace app

#endif /* FLASHY_DINGLER_PATTERN_H_ */
