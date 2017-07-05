#ifndef CLOCKING_H_
#define CLOCKING_H_

/**
 * @file Clocking.h
 *
 * @details Contains the declaration of the Clocking class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */


namespace mcu {

//
// Clocking Class Declaration
//

/**
 * Encapsulates core MCU clock configuration. Instantiating this class will
 * configure the MCU clock.
 */
class Clocking {
 public:
  Clocking(uint32_t freq);
  ~Clocking();

  // Disallow copy and assign.
  Clocking(const Clocking&) = delete;
  Clocking& operator=(const Clocking&) = delete;
};

} // namespace mcu

#endif /* CLOCKING_H_ */
