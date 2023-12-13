#include "PinMappings.h"

#if defined(ARDUINO_GIGA)

int ADC1PinRemap(int Pin) {
  switch (Pin) {
    case 100: return (0);
    case 101: return (1);
    case 56: return (3);
    case A3: return (5);
    case A0: return (4);
    case 5: return (7);
    case A1: return (8);
    case A2: return (9);
    case A6: return (10);
    case 73: return (11);
    case A5: return (12);
    case A4: return (13);
    case 3: return (14);
    case 2: return (15);
    case A7: return (16);
    case 66: return (17);
    case DAC_0: return (18);
    case DAC_1: return (19);
  default: return(0);
  };
}

int ADC2PinRemap(int Pin) {
  switch (Pin) {
    case 100: return (0);
    case 101: return (1);
    case 56: return (3);
    case A0: return (4);
    case A3: return (5);
    case 5: return (7);
    case A1: return (8);
    case A2: return (9);
    case A6: return (10);
    case 73: return (11);
    case A5: return (12);
    case A4: return (13);
    case 3: return (14);
    case 2: return (15);
    case DAC_0: return (18);
    case DAC_1: return (19);
  default: return(0);
  };
}

int ADC3PinRemap(int Pin) {
  switch (Pin) {
    case 102: return (0);
    case 103: return (1);
    case A6: return (10);
    case 73: return (11);
    case A5: return (12);
    case 21: return (15);
  default: return(0);
  };
}

//#elif defined(ARDUINO_PORTENTA_H7)
#else

int ADC1PinRemap(int Pin) {
  return (Pin);
}

int ADC2PinRemap(int Pin) {
  return (Pin);
}

int ADC3PinRemap(int Pin) {
  return (Pin);
}
#endif
