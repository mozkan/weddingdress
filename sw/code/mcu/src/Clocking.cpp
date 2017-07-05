/**
 * @file Clocking.cpp
 *
 * @details Contains the Implementation of the Clocking class.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "chip.h"

#include "Clocking.h"


namespace mcu {

//
// Clocking Class Definition
//

Clocking::Clocking(uint32_t freq) {
  Chip_SetupIrcClocking(freq);
}

Clocking::~Clocking() { }

} // namespace mcu
