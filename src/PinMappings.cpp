#include "PinMappings.h"

#if defined(ARDUINO_GIGA)

int ADC1PinRemap(int Pin) {
  switch (Pin) {
    case A0: return (4);
    case A1: return (8);
    case A2: return (9);
    case A3: return (5);
    case A4: return (13);
    case A5: return (12);
    case A6: return (10);
    case A7: return (16);
    case 100: return (0);
    case 101: return (1);
    case DAC_1: return (19);
  default: return(0);
  };
}

int ADC2PinRemap(int Pin) {
  switch (Pin) {
    case A0: return (4);
    case A1: return (8);
    case A2: return (9);
    case A3: return (5);
    case A4: return (13);
    case A5: return (12);
    case A6: return (10);
    case 100: return (0);
    case 101: return (1);
    case DAC_1: return (19);
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
#endif
