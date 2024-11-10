
#include "ADCConfig.h"
#include "PinMappings.h"


ADC_TypeDef* ADCList[3] = { ADC1, ADC2, ADC3 };  //Stores information on if ADC1 is Initialized
bool ADCInitialized[3] = { 0, 0, 0 };            //Stores information on if ADC1 is Initialized
int Prescaler = 0;                               //Stores the Calculated Prescaler value
bool ClockInitialized = 0;                       //Stores if clock is initialized
double ActualFrequency = 0;

int GetADCNumber(ADC_TypeDef* ADC) {
  if (ADC == ADC1) {
    return (0);
  } else if (ADC == ADC2) {
    return (1);
  } else {
    return (2);
  };
}


void ADCInterleaved(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ) {

  if (!ClockInitialized) { SystemCLCKInit(ClockSpeedMHZ); };    //Initiate System clock
  ADC_Init(ADC1, ADCChannel, Resolution, Differential, 0, 0);   //Initiate ADC1
  ADC_Init(ADC2, ADCChannel, Resolution, Differential, 0, 0);   //Initiate ADC2
  SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DUAL_0 | ADC_CCR_DUAL_1);  //Configures Interleaved mode
  ADCEN(ADC1);                                                  //Enable ADC1
  ADCEN(ADC2);                                                  //Enable ADC2
  ADC_Start(ADC1);                                              //Starts the conversions

}  //Initiates and starts ADC1 and ADC2 in Interleaved modes.

void ADCSimultaneous(int ADC1Channel, int ADC2Channel, int Resolution, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

  if (!ClockInitialized) { SystemCLCKInit(ClockSpeedMHZ); };          //Initiate System clock
  ADC_Init(ADC1, ADC1Channel, Resolution, 0, SampleTime, Samplenum);  //Initiate ADC1
  ADC_Init(ADC2, ADC2Channel, Resolution, 0, SampleTime, Samplenum);  //Initiate ADC2
  SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DUAL_0);                         //Configure Simultaneous mode
  ADCEN(ADC1);                                                        //Enable ADC1
  ADCEN(ADC2);                                                        //Enable ADC2
  ADC_Start(ADC1);                                                    //Starts the conversions

}  //Initiates and starts ADC1 and ADC2 in Simultaneous modes.


void ADCBegin(ADC_TypeDef* ADC, int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

  if (!ClockInitialized) { SystemCLCKInit(ClockSpeedMHZ); };                   //Initiate System clock
  ADC_Init(ADC, ADCChannel, Resolution, Differential, SampleTime, Samplenum);  //Initiate ADC1
  ADCEN(ADC);                                                                  //Enable ADC1
  ADC_Start(ADC);                                                              //Start ADC1 conversions


}  //Initiates and starts ADC1


void ADCInitialize(ADC_TypeDef* ADC, int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {

  //Set boost mode so ADC can run faster

  if (ActualFrequency > 50) {
    SET_BIT(ADC->CR, ADC_CR_BOOST);
  } else if (ActualFrequency > 25) {
    SET_BIT(ADC->CR, ADC_CR_BOOST_1);
  } else if (ActualFrequency > 12.5) {
    SET_BIT(ADC->CR, ADC_CR_BOOST_0);
  };

  /***************ADC not Enabled yet********************/

  CLEAR_BIT(ADC->CR, ADC_CR_DEEPPWD);  //Wake up from deep sleep

  SET_BIT(ADC->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator


  //ADC CALIBRATION

  if (Differential) {
    SET_BIT(ADC->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC->CR, ADC_CR_ADCALLIN | ADC_CR_ADCAL);
  while (READ_REG(ADC->CR & ADC_CR_ADCAL)) {};


  SET_BIT(ADC->CFGR2, ADC_CFGR2_ROVSE);  //Set oversampling


  ADC->CFGR2 += 65536 * Samplenum;  //Set number of samples

  ADC->PCSEL = 0xFFFFF;  //Enable all channels

  ADC->SQR1 = 64 * AdcChannel;  //Select channel

  ADC->DIFSEL = 1048575 * Differential;  //Enable differential mode if needed

  SET_BIT(ADC->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  ResolutionSet(ADC, Resolution);  //Set resolution

  ADC->SMPR1 = SampleTime;  //Set sampletime

  // ADCInitialized = ADc
}


void ADC_Init(ADC_TypeDef* ADC, int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {
  ADCInitialize(ADC, ADCPinRemap(ADC, AdcChannel), Resolution, Differential, SampleTime, Samplenum);
  ADCInitialized[GetADCNumber(ADC)] = 1;  //sort out
}



void ADCEN(ADC_TypeDef* ADC) {
  if (ADC == ADC3) {
    ADC3_COMMON->CCR |= Prescaler << 18;  //Set Prescaler value
  } else {
    ADC12_COMMON->CCR |= Prescaler << 18;  //Set Prescaler value
  };

  SET_BIT(ADC->CR, ADC_CR_ADEN_Msk);  //Enable

}


void ADC_Start(ADC_TypeDef* ADC) {

  while (!READ_REG(ADC->ISR & ADC_ISR_ADRDY)) {};  //Wait for ADC to be ready to start

  SET_BIT(ADC->CR, ADC_CR_ADSTART_Msk);  //Start
}


void ADC_Stop(ADC_TypeDef* ADC) {

  SET_BIT(ADC->CR, ADC_CR_ADSTP);               //Stop the ADC
  while (READ_REG(ADC->CR & ADC_CR_ADSTP)) {};  //Wait for ADC to stop
}

void ADCChangeChannel(ADC_TypeDef* ADC, int AdcChannel) {
  bool ADActive = READ_REG(ADC->CR & ADC_CR_ADSTART);  //Check if ADC is active
  if (ADActive) { ADC_Stop(ADC); };                    //Stop the ADC if active

  while (READ_REG(ADC->CR & ADC_CR_ADSTP) || READ_REG(ADC->CR & ADC_CR_JADSTART)) {};  //Wait for ADC to stop
  ADC->SQR1 = 64 * ADCPinRemap(ADC, AdcChannel);                                       //Set ADC Channel

  if (ADActive) { ADC_Start(ADC); };  //If ADC was initially active turn it back on
}



void ResolutionSet(ADC_TypeDef* ADC, int Resolution) {
  //Sets Resolution for the ADC
  CLEAR_BIT(ADC->CFGR, ADC_CFGR_RES);

  switch (Resolution) {
    case 8: SET_BIT(ADC->CFGR, ADC_CFGR_RES);
    case 10: SET_BIT(ADC->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_1);
    case 12: SET_BIT(ADC->CFGR, ADC_CFGR_RES_2 | ADC_CFGR_RES_1);
    case 14: SET_BIT(ADC->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_2);
    default: return;
  };
}



void SystemCLCKInit(double ClockSpeedMHZ) {

#if defined(ARDUINO_GIGA)
  RCC->PLLCKSELR = 0x0200F022;  //Divide 16mhz clock to 1
#elif defined(STM32H747xx)
  RCC->PLLCKSELR = 0x02017022;  //Divide 24mhz clock to 1
#else
#error Unsupported microcontroller, this library currently only works for STM32H747 based arduino boards.
#endif

  ClockSpeedMHZ *= 2;  //ADC always further divides clockspeed by 2, compensate
                       //Calculate proper prescaler if needed

  int AdcPrescDivision[12] = { 1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256 };

  for (int i = 1; i < 12; i++) {
    if (AdcPrescDivision[i] < 1.2 / ClockSpeedMHZ) {
      Prescaler = i;
    };
  }

  //Calculate dividor to use

  int dividor = ceil(150.0f / ClockSpeedMHZ / AdcPrescDivision[Prescaler]);

  dividor = constrain(dividor, 1, 128);

  int multiplier = floor(ClockSpeedMHZ * dividor * AdcPrescDivision[Prescaler]);

  multiplier = constrain(multiplier, 4, 512);


  int FracMultiplier = floor(8192 * (ClockSpeedMHZ * dividor * AdcPrescDivision[Prescaler] - floor(ClockSpeedMHZ * dividor * AdcPrescDivision[Prescaler])));


  FracMultiplier = constrain(FracMultiplier, 0, 8192);


  if (FracMultiplier != 0) {
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN);
  };


  ActualFrequency = (multiplier + double(FracMultiplier) / 8192) / AdcPrescDivision[Prescaler] / dividor / 2;
  //See how Rounding affected the frequency, move the ceil part before

  //Set generator speed, remain in 150-300mhz range as long as possible
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL);

  RCC->PLL2DIVR = 0x100FDFF + dividor * 512 + multiplier;  //Sets the generator speed
  RCC->PLL2FRACR = 8 * FracMultiplier - 8;


  SET_BIT(RCC->CR, RCC_CR_PLL2ON);             //Enable generator
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_DIVP2EN);  //Enable output


  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN_Msk | RCC_AHB1ENR_DMA1EN);                                          //Enable ADC 1 and 2 and DMA1
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_ADC3EN);  //Enable GPIOs and ADC3
}



int CatchADCValue(ADC_TypeDef* ADC, uint32_t Timeout) {
  uint32_t InitMicros = micros();                                                       //Capture current time
  while (!READ_REG(ADC->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {};  //Wait for a new value if the latest one was already read
  return (READ_REG(ADC->DR));                                                           //Return the new value
}


int FastAnalogRead(int Pin, uint32_t Timeout) {  //Fix the double remap

  for (int i = 0; i < 3; i++) {
    if (ADCInitialized[i] && ADCPinRemap(ADCList[i], Pin) != -1) {
      return (ADCInjectedRead(ADCList[i], Pin, Timeout));
    };
  };
  if (!ADCInitialized[0] && ADCPinRemap(ADC1, Pin) != -1) {
    return (ADCInjectedRead(ADC1, Pin, Timeout));
  } else if (!ADCInitialized[2] && ADCPinRemap(ADC3, Pin) != -1) {
    return (ADCInjectedRead(ADC3, Pin, Timeout));
  } else {
    return (-1);
  };


}  //Quickly read a pin from the first initiated ADC using injected conversion - not stopping usual conversion, or Initiate first in order ADC and read.

int ADCInjectedRead(ADC_TypeDef* ADC, int ADCChannel, uint32_t Timeout) {
  if (!ADCInitialized[GetADCNumber(ADC)]) {  //Fix
    ADCBegin(ADC);
  };                                                                                     //Begin ADC if not initialized
  ADC->JSQR = 512 * ADCPinRemap(ADC, ADCChannel);                                        //Set the injected pin to ID
  while (!READ_REG(ADC->ISR & ADC_ISR_ADRDY)) {};                                        //Wait for ADC to be ready
  uint32_t InitMicros = micros();                                                        //Capture current time
  SET_BIT(ADC->CR, ADC_CR_JADSTART);                                                     //Start the conversion
  while (!READ_REG(ADC->ISR & ADC_ISR_JEOC) && (micros() < (Timeout + InitMicros))) {};  //Wait for a new value if the latest one was already read
  return (READ_REG(ADC->JDR1));                                                          //Return the new value
}

double GetADCFrequency() {
  return (ActualFrequency);
}

