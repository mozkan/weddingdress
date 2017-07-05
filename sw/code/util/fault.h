#ifndef FAULT_H_
#define FAULT_H_

#include "chip.h"

#ifdef DEBUG

#define ASSERT(x) \
  do {\
    if (!(x)) {\
      Chip_GPIO_SetPinState(LPC_GPIO, 0, 18, true);\
      while (1) { }\
    }\
  } while(0)

#else

#define ASSERT(x) ((void)0)

#endif

#endif /* FAULT_H_ */
