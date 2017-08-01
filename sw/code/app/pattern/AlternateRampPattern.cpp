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


namespace app {
namespace pattern {

//
// Task Class Definition
//

AlternateRampPattern::AlternateRampPattern(hal::Display& display) 
  : Pattern(display), temp_(0) { }

AlternateRampPattern::~AlternateRampPattern() { }


//
// Private Member Definitions
//

void AlternateRampPattern::CalculateNextIteration(void) {
  temp_++;

  if (temp_  & 0x01) {
    buffer_[0][0].set_r(55);
    buffer_[0][0].set_g(55);
    buffer_[0][0].set_b(55);
  } else {
    buffer_[0][0].set_r(0);
    buffer_[0][0].set_g(0);
    buffer_[0][0].set_b(0);
  }
}

} // namespace pattern
} // namespace app
