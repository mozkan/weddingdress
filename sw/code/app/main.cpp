#include <cstdint>

#include <vector>

#include "chip.h"

#include "fault.h"

#include "MCU.h"
#include "MCUConfig.h"

#include "APA102Pixel.h"
#include "Display.h"
#include "Wedfestdress.h"


int main(void) {
  hal::Wedfestdress dress;

  hal::Display& display = dress.GetDisplay();

  //std::vector<hal::APA102Pixel> single_string(2, hal::APA102Pixel(1, 3, 7, 15));
  std::array<std::vector<hal::APA102Pixel>, hal::Display::kNumberOfStrings>
    all_strings = {{
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
      std::vector<hal::APA102Pixel>(25, hal::APA102Pixel(1, 3, 7, 5)),
    }};
  
#if 0
  hal::Timing& timing = dress.GetTiming();

  uint32_t last_millis = timing.Millis();
  uint32_t poll_time = timing.Millis();

  while (1) {
    while ((poll_time - last_millis) < 1000) {
      poll_time = timing.Millis();
    }
    last_millis = poll_time;
    all_strings[0][0].set_r(255);
    all_strings[0][0].set_g(255);
    all_strings[0][0].set_b(255);
    display.Update(all_strings);

    while ((poll_time - last_millis) < 1000) {
      poll_time = timing.Millis();
    }
    last_millis = poll_time;
    all_strings[0][0].set_r(0);
    all_strings[0][0].set_g(0);
    all_strings[0][0].set_b(0);
    display.Update(all_strings);
  }
#endif

#if 0
  while(1) {
    //display.Update(single_string);
    for (int string = 0; string < 6; string++) {
      for (int i = 0; i < 25; i++) {
        all_strings[string][i] = hal::APA102Pixel(100, 5, 6, 31);
        //all_strings[string][i] = hal::APA102Pixel(186, 37, 148, 31);
        //all_strings[string][i] = hal::APA102Pixel(255, 246, 173, 31);

        display.Update(all_strings);
        //for (int i = 0; i < 10000; i++) { }
      }
    }

    for (int string = 0; string < 6; string++) {
      for (int i = 0; i < 25; i++) {
        all_strings[string][i] = hal::APA102Pixel(10, 5, 5, 31);
        all_strings[string][i] = hal::APA102Pixel(5, 10, 5, 31);
        all_strings[string][i] = hal::APA102Pixel(5, 5, 10, 31);
        all_strings[string][i] = hal::APA102Pixel(10, 10, 5, 31);
        all_strings[string][i] = hal::APA102Pixel(5, 10, 10, 31);
        all_strings[string][i] = hal::APA102Pixel(10, 5, 10, 31);

        display.Update(all_strings);
        for (int i = 0; i < 10000; i++) { }
      }
    }
  }
#endif

#if 1
  uint8_t count = 0;
  int8_t  direction = 1;

  while (1) {
    if (count == 255) {
      direction = -1;
    } else if (count == 0) {
      direction = 1;
    }

    for (int string = 0; string < 6; string++) {
      for (int i = 0; i < 25; i++) {
        all_strings[string][i].set_r(count);
        all_strings[string][i].set_g(count);
        all_strings[string][i].set_b(count);
      }
    }

    display.Update(all_strings);
    count += direction;
  }
#endif

  return 0;
}
