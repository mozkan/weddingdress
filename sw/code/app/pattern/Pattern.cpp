/**
 * @file Pattern.cpp
 *
 * @details Contains the implementation of the Pattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "Pattern.h"

#include <vector>

#include "APA102Pixel.h"


namespace app {
namespace pattern {

//
// Task Class Definition
//

Pattern::Pattern(hal::Display& display) 
  : display_(display),
    buffer_{{
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 31))
    }} { }

Pattern::~Pattern() { }

void Pattern::Update(void) {
  CalculateNextIteration();
  display_.Update(buffer_);
}

void Pattern::Reset(void) {
  for (auto& string : buffer_) {
    for (auto& led : string) {
      led.set_r(0);
      led.set_g(0);
      led.set_b(0);
    }
  }
}

} // namespace pattern
} // namespace app
