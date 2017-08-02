#ifndef PATTERN_HELPERS_H_
#define PATTERN_HELPERS_H_

/**
 * @file PatternHelpers.h
 *
 * @details Header file for declarations of helper functions for pattern related
 * math and data manipulation.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include <cstdint>


namespace app {
namespace pattern {

/**
 * Adds two unsigned 8-bit integers together and saturates the sum at 255.
 *
 * @param[in] add1 The first integer to add.
 * @param[in] add2 The second integer to add.
 * @return The sum of the two integers, saturated at 255 if necessary.
 */
uint8_t Add8Sat(uint8_t add1, uint8_t add2);

/**
 * Add8Sat variant that takes a signed integer as the second argument. Saturates
 * at 0 for negative sums and 255 for positive sums.
 */
uint8_t Add8Sat(uint8_t add1, int8_t add2);

/**
 * Subtracts two unsigned 8-boit integers. Saturates their result at 0 if it is
 * negative.
 *
 * @param[in] minuend The number being subtracted from.
 * @param[in] subtrahend The number being subtracted.
 * @return The difference between the minuend and the subtrahend, saturated at 0
 *     if it is negative.
 */
uint8_t Sub8Sat(uint8_t minuend, uint8_t subtrahend);

/**
 * Sub8Sat variant that takes a signed integer as the second argument. Saturates
 * at 0 for negative sums and 255 for positive sums.
 */
uint8_t Sub8Sat(uint8_t minuend, int8_t subtrahend);

} // namespace pattern
} // namespace app

#endif /* PATTERN_HELPERS_H_ */
