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

#include "Display.h"

#include "Pattern.h"


namespace app {
namespace pattern {

//
// AlternateRampPattern Class Declaration
//

/**
 * Generates a pattern that ramps up even pixels while ramping down odd pixels.
 * Once the limit is reached, the ramp directions change. Does this with  white
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
  virtual void CalculateNextIteration(void);

  uint8_t temp_;
};

} // namespace pattern
} // namespace app

#endif /* ALTERNATE_RAMP_PATTERN_H_ */
