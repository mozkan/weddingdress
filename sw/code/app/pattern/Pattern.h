#ifndef PATTERN_H_
#define PATTERN_H_

/**
 * @file Pattern.h
 *
 * @details Header file for the declaration of the Pattern class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "Display.h"


namespace app {
namespace pattern {

//
// Pattern Class Declaration
//

/**
 * Abstrat class representing a graphical pattern to be displayed on the dress.
 * Processes iterations of the pattern but does not manage timing.
 */
class Pattern {
 public:
  /**
   * Constructor for the Pattern class.
   *
   */
  Pattern(hal::Display& display);

  virtual ~Pattern();

  /**
   * Runs the next iteration of the pattern.
   *
   * @return Nothing.
   */
  void Update(void);

  // Disallow copy and assign.
  Pattern(const Pattern&) = delete;
  Pattern& operator=(const Pattern&) = delete;

 protected:
  virtual void CalculateNextIteration(void) = 0;

  hal::Display& display_;
  hal::Display::DisplayBuffer buffer_;
};

} // namespace pattern
} // namespace app

#endif /* PATTERN_H_ */
