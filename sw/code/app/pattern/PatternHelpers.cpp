/**
 * @file PatternHelpers.cpp
 *
 * @details Contains the implementation of the PatternHelpers fuctions.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "PatternHelpers.h"


namespace app {
namespace pattern {

namespace {

uint8_t CommonAdd8Sat(int16_t add1, int16_t add2) {
  int16_t sum = add1 + add2;

  if (sum < 0) {
    sum = 0;
  } else if (sum > 255) {
    sum = 255;
  }

  return static_cast<uint8_t>(sum);
}

uint8_t CommonSub8Sat(int16_t minuend, int16_t subtrahend) {
  int16_t difference = minuend - subtrahend;

  if (difference < 0) {
    difference = 0;
  } else if (difference > 255) {
    difference = 255;
  }

  return static_cast<uint8_t>(difference);
}

} // namespace

uint8_t Add8Sat(uint8_t add1, uint8_t add2) {
  return CommonAdd8Sat(static_cast<int16_t>(add1), static_cast<int16_t>(add2));
}

uint8_t Add8Sat(uint8_t add1, int8_t add2) {
  return CommonAdd8Sat(static_cast<int16_t>(add1), static_cast<int16_t>(add2));
}

uint8_t Sub8Sat(uint8_t minuend, uint8_t subtrahend) {
  return CommonSub8Sat(static_cast<int16_t>(minuend),
                       static_cast<int16_t>(subtrahend));
}

uint8_t Sub8Sat(uint8_t minuend, int8_t subtrahend) {
  return CommonSub8Sat(static_cast<int16_t>(minuend),
                       static_cast<int16_t>(subtrahend));
}

} // namespace pattern
} // namespace app
