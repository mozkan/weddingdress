/**
 * @file PWM16.cpp
 *
 * @details Contains the Implementation of the PWM16 class. Note that the
 * interface to this class represents a 16-bit PWM, but may not yield a fast
 * enough PWM frequency so the true bit-depth of the PWM can be made lower than
 * 16-bits via kTrueBitDepth.
 *
 * @author Murat Ozkan
 *
 * Wedfestdress Firmware 2017
 */

#include "PWM16.h"


//
// Module Variables
//

namespace mcu {

namespace {

//
// Types
//
#if 0
struct PWMParams {
  LPC_TIMER_T*       timer;
  int8_t             output_match_ch;
  int8_t             reset_match_ch;
  LPC11CXX_IRQn_Type irq;
};
#endif


//
// Constants
//

#if 0
const PWMParams kPWMs[6] = {
  { LPC_TIMER16_0, 0, 3, TIMER_16_0_IRQn }, //kCT16B0Mat0
  { LPC_TIMER16_0, 1, 3, TIMER_16_0_IRQn }, //kCT16B0Mat1
  { LPC_TIMER32_0, 0, 3, TIMER_32_0_IRQn }, //kCT32B0Mat0
  { LPC_TIMER32_0, 1, 3, TIMER_32_0_IRQn }, //kCT32B0Mat1
  { LPC_TIMER32_1, 0, 3, TIMER_32_1_IRQn }, //kCT32B1Mat0
  { LPC_TIMER32_1, 1, 3, TIMER_32_1_IRQn }  //kCT32B1Mat1
};

constexpr uint32_t kPrescaleValue = 0;
constexpr uint32_t kTrueBitDepth  = 14; //bits
constexpr uint32_t kBitReduction  = 16 - kTrueBitDepth;
constexpr uint32_t kPeriodTicks   = 0xFFFF >> kBitReduction;
#endif
}


//
// PWM16 Class Definition
//

PWM16::PWM16(PWMChannels /*channel*/)
#if 0
  : timer_(kPWMs[static_cast<int>(channel)].timer),
    output_match_ch_(kPWMs[static_cast<int>(channel)].output_match_ch),
    reset_match_ch_(kPWMs[static_cast<int>(channel)].reset_match_ch),
    irq_(kPWMs[static_cast<int>(channel)].irq)
#endif
{
#if 0
  Chip_TIMER_Init(timer_);

  // Set prescaler.
  Chip_TIMER_PrescaleSet(timer_, kPrescaleValue);

  // Set the match channel that resets the PWM period.
  Chip_TIMER_ResetOnMatchEnable(timer_, reset_match_ch_);

  // Set the period.
  Chip_TIMER_SetMatch(timer_, reset_match_ch_, kPeriodTicks);

  // Enable PWM mode on this timer.
  timer_->PWMC |= (1 << output_match_ch_);

  // Set the default duty cycle to 0%
  SetDutyCycle(0);

  // Start timer.
  Chip_TIMER_Enable(timer_);
#endif
}

PWM16::~PWM16() { }

void PWM16::SetDutyCycle(uint16_t /*dutycycle*/) {
#if 0
  // Match the bit-depth of the duty cycle to the bit-depth of the PWM.
  uint32_t real_dutycycle = dutycycle >> kBitReduction;

  // Invert polarity.
  uint32_t match_value = kPeriodTicks - real_dutycycle;

  Chip_TIMER_SetMatch(timer_, output_match_ch_, match_value);
#endif
}

void PWM16::Stop(void) {
#if 0
  timer_->TCR = 0x2;
#endif
}

void PWM16::Restart(void) {
#if 0
  timer_->TCR = 0x1;
#endif
}

void PWM16::ConfigureEndOfPeriodInterrupt(InterruptState /*state*/) {
#if 0
  if (state == InterruptState::kEnable) {
    NVIC_EnableIRQ(irq_);
    Chip_TIMER_MatchEnableInt(timer_, reset_match_ch_);
  }
  else {
    NVIC_DisableIRQ(irq_);
    Chip_TIMER_MatchDisableInt(timer_, reset_match_ch_);
  }
#endif
}

} // namespace mcu
