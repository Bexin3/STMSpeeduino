#include "PinMappings.h"

#if defined(ARDUINO_GIGA)

int ADCPinRemap(ADC_TypeDef* ADC, int Pin) {


  switch (Pin) {

    case A6: return (10);
    case 73: return (11);
    case A5:
      return (12);

      if (ADC == ADC3) {

        case 102: return (0);
        case 103: return (1);
        case 21: return (15);

      } else {

        case 100: return (0);
        case 101: return (1);
        case 56: return (3);
        case A3: return (5);
        case A0: return (4);
        case 5: return (7);
        case A1: return (8);
        case A2: return (9);
        case A4: return (13);
        case 3: return (14);
        case 2: return (15);
        case A7: return (16);
        case 66:
          if (ADC == ADC1) {
            return (17);
          } else {
            return (-1);
          };
        case DAC_0: return (18);
        case DAC_1: return (19);

      }  //Remap pins to channel IDs

    default: return (-1);
  };
}

//#elif defined(ARDUINO_PORTENTA_H7)
#else

int ADCPinRemap(ADC_TypeDef* ADC, int Pin) {
  return (Pin);
}  //Return raw Pin if unadded board

#endif
