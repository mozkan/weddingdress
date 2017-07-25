#ifndef TIMING_H_
#define TIMING_H_
/**
 * @file Timing.h
 *
 * @details Contains the declaration of the Timing class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include <cstdint>

#include "Timer.h"


namespace hal {

//
// Timing Class Declaration
//

/**
 * Driver class to implement system-level timing functions.
 */
class Timing
{
 public:
  /**
   * Constructor for the Timing class.
   *
   * @param[in] timer The timer resource to use to implement system-level timing
   *     functions.
   */
  Timing(mcu::Timer& timer);

  ~Timing();

  /*
   * Returns the value of a fre-running 32-bit millisecond counter.
   *
   * @return Milliseconds since the system started operating.
   */
  uint32_t Millis(void);

  // Disallow copy and assign.
  Timing(const Timing&) = delete;
  Timing& operator=(const Timing&) = delete;

 private:
  mcu::Timer& timer_;
};

} // namespace hal

#endif /* TIMING_H_ */
