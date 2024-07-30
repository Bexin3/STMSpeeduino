#include "Opamp.h"

#if defined(ARDUINO_PORTENTA_H7_M7)
#pragma message "There are no OPAMP pins abailable on the portenta"
#endif

void OPAMPCFG(int Gain) {

  // SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN);

  SET_BIT(RCC->APB1HENR, RCC_APB1HENR_OPAMPEN);                                                                             //Enable power for the Opamp
  OPAMP1->CSR = 0;                                                                                                          //Set up opamp 1
  SET_BIT(OPAMP1->CSR, OPAMP_CSR_CALSEL_1 | OPAMP_CSR_OPAHSM | OPAMP_CSR_OPAMPxEN | OPAMP_CSR_VMSEL_1 | OPAMP_CSR_CALOUT);  //Setup OPAMP1 further
  //Set Gain
  if (Gain == 16) {
    SET_BIT(OPAMP1->CSR, OPAMP_CSR_PGGAIN_0 | OPAMP_CSR_PGGAIN_1);
  } else if (Gain == 8) {
    SET_BIT(OPAMP1->CSR, OPAMP_CSR_PGGAIN_1);
  } else if (Gain == 4) {
    SET_BIT(OPAMP1->CSR, OPAMP_CSR_PGGAIN_0);
  };
}
