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
  
  all_strings[0][1] = hal::APA102Pixel(4, 5, 6, 15);
  all_strings[1][2] = hal::APA102Pixel(4, 5, 6, 15);
  all_strings[2][3] = hal::APA102Pixel(4, 5, 6, 15);
  all_strings[3][4] = hal::APA102Pixel(4, 5, 6, 15);
  all_strings[4][5] = hal::APA102Pixel(4, 5, 6, 15);
  all_strings[5][6] = hal::APA102Pixel(4, 5, 6, 15);

  while(1) {
    //display.Update(single_string);
    display.Update(all_strings);
  }

  return 0;
}
