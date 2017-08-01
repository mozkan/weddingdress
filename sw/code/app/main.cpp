#include <cstdint>

#include "Display.h"
#include "Wedfestdress.h"

#include "pattern/AlternateRampPattern.h"


int main(void) {
  hal::Wedfestdress dress;

  hal::Display& display = dress.GetDisplay();

  app::pattern::AlternateRampPattern al_pattern(display);
  app::pattern::Pattern& pattern = al_pattern;

  hal::Timing& timing = dress.GetTiming();

  uint32_t last_millis = timing.Millis();
  uint32_t poll_time = timing.Millis();

  while (1) {
    while ((poll_time - last_millis) < 1000) {
      poll_time = timing.Millis();
    }

    last_millis = poll_time;
    pattern.Update();
  }

  return 0;
}
