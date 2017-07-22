#ifndef WEDFESTDRESS_H_
#define WEDFESTDRESS_H_

/**
 * @file Wedfestdress.h
 *
 * @details Header file for the Wedfestdress class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

//
// Includes
//

#include "MCU.h"

#include "Display.h"


namespace hal {

//
// Wedfestdress Class Declaration
//

/**
 * The Wedfestdress class provides a single point of access to all high-level
 * board and system functions. Instantiating it will allocate and initialize all
 * dependent hardware and software resources.
 */
class Wedfestdress
{
 public:
  Wedfestdress();
  ~Wedfestdress();

  /**
   * Accessor to the display mechanism.
   *
   * @return Reference to the Display on this Wedfestdress.
   */
  Display& GetDisplay(void);

  /**
   * Accessor to the system-level timing resource.
   *
   * @return Reference to the Timing resource on this Wedfestdress.
   */
  //Timing& GetTiming(void);

  /**
   * Accessor to the system-level audio measurement resource.
   *
   * @return Reference to the Microphone resource on this Wedfestdress.
   */
  //Microphone& GetMicrophone(void);

  /**
   * Accessor to the system-level user input resource.
   *
   * @return Reference to the UserInput resource on this Wedfestdress.
   */
  //UserInput& GetUserInput(void);

  /**
   * Accessor to the system-level battery resource.
   *
   * @return Reference to the Battery resource on this Wedfestdress.
   */
  //Battery& GetBattery(void);

  // Disallow copy and assign.
  Wedfestdress(const Wedfestdress&) = delete;
  Wedfestdress& operator=(const Wedfestdress&) = delete;

 private:
  static bool initialized_;

  // Must be at the top of the member list. Initializes all MCU functions.
  mcu::MCU mcu_;

  // HAL classes.
  Display display_;
};

} // namespace hal

#endif /* WEDFESTDRESS_H_ */
