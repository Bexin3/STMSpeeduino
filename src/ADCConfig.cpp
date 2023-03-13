
#include "ADCConfig.h"
#include "PinMappings.h"


int Prescaler = 0;
void ADCInterleaved(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ) {

SystemCLCKInit(ClockSpeedMHZ);
ADC1_Init(ADCChannel, Resolution, Differential, 0, 0);
ADC2_Init(ADCChannel, Resolution, Differential, 0, 0);
ADCInterleaved_Start(Resolution);

}

void ADCSimultaneous(int ADC1Channel, int ADC2Channel, int Resolution, double ClockSpeedMHZ, int SampleTime, int Samplenum) {


SystemCLCKInit(ClockSpeedMHZ);
ADC1_Init(ADC1Channel, Resolution, 0, SampleTime, Samplenum);
ADC2_Init(ADC2Channel, Resolution, 0, SampleTime, Samplenum);
ADCSimultaneous_Start();


}

void ADC1Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

SystemCLCKInit(ClockSpeedMHZ);
ADC1_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum);
ADC1_Start();

}

void ADC2Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

SystemCLCKInit(ClockSpeedMHZ);
ADC2_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum);
ADC2_Start();

}





void ADC1_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {


  //GPIOA PORT 1------------------------------------

  

  /***************ADC not Enabled yet********************/

  CLEAR_BIT(ADC1->CR, ADC_CR_DEEPPWD);     //Wake up from deep sleep

  SET_BIT(ADC1->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator


  AdcChannel=ADC1PinRemap(AdcChannel);     //Get actual channel number
  
  //ADC CALIBRATION-----------------------------------

  if(Differential) {
  SET_BIT(ADC1->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC1->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC1->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC1->CR & ADC_CR_ADCAL)) {};

  
  SET_BIT(ADC1->CFGR2, ADC_CFGR2_ROVSE); //Set oversampling

  
  ADC1->CFGR2 += 65536 * Samplenum; //Set number of samples


  //Select channel

  if (Differential) {

  
  SET_BIT(ADC1->PCSEL, ADC_PCSEL_PCSEL_0 | ADC_PCSEL_PCSEL_1);

  ADC1->SQR1 = 64;

  } else {

  ADC1->PCSEL = 1 << AdcChannel;

  ADC1->SQR1 = 64 * AdcChannel;
  };





  ADC1->DIFSEL = 1048575 * Differential;  //Diffmode



  SET_BIT(ADC1->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk);  //Enable Continuous mode, Always overwrite data

  ResolutionSet(Resolution);  //Set resolution



  ADC1->SMPR1 = SampleTime * 153391689;  //Set sampletime
  ADC1->SMPR2 = SampleTime * 153391689;  //Set sampletime



  SET_BIT(ADC1->CR, ADC_CR_ADEN_Msk);                               //Enable ADC
  

}


void ADC2_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {



  /***************ADC not Enabled yet********************/


  //Enable the voltage generator  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator

  CLEAR_BIT(ADC2->CR, ADC_CR_DEEPPWD);

  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator
  //ADC CALIBRATION-----------------------------------

  AdcChannel=ADC2PinRemap(AdcChannel);

  if(Differential) {
  SET_BIT(ADC2->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC2->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC2->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC2->CR & ADC_CR_ADCAL)) {};

  SET_BIT(ADC2->CFGR2, ADC_CFGR2_ROVSE);

  ADC2->CFGR2 += 65536 * Samplenum;




  if (Differential) {

  
  SET_BIT(ADC2->PCSEL, ADC_PCSEL_PCSEL_0 | ADC_PCSEL_PCSEL_1);

  ADC2->SQR1 = 64;

  } else {

  ADC2->PCSEL = 1 << AdcChannel;

  ADC2->SQR1 = 64 * AdcChannel;
  };



  ADC2->DIFSEL = 1048575 * Differential;  //Diffmode?



  SET_BIT(ADC2->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk);  //Enable Continuous mode, Always overwrite data

  Resolution2Set(Resolution);  //Set RESOLUTION



  ADC2->SMPR1 = SampleTime * 153391689;  //Divide
  ADC2->SMPR2 = SampleTime * 153391689;  //Divide


  SET_BIT(ADC2->CR, ADC_CR_ADEN_Msk);  

}





void Resolution2Set(int Resolution) {

  //Sets Resolution

  CLEAR_BIT(ADC2->CFGR, ADC_CFGR_RES);

  switch (Resolution) {
    case 8:
      SET_BIT(ADC2->CFGR, ADC_CFGR_RES);
      break;
    case 10:
      SET_BIT(ADC2->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_1);
      break;
    case 12:
      SET_BIT(ADC2->CFGR, ADC_CFGR_RES_2 | ADC_CFGR_RES_1);
      break;
    case 14:
      SET_BIT(ADC2->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_2);
      break;
    default:
      break;
  };
}



void ADCInterleaved_Start(int Resolution) {  

ADC12_COMMON->CCR += 262144*Prescaler;

if (Resolution = 16) {
   ADC12_COMMON->CCR = 7+(2*256);
} else {
   ADC12_COMMON->CCR = 7+(1*256);
};


  while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};
  while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};


  SET_BIT(ADC1->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADCSimultaneous_Start() {  

ADC12_COMMON->CCR += 262144*Prescaler;

   ADC12_COMMON->CCR = 6;


  while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};
  while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};


  SET_BIT(ADC1->CR, ADC_CR_ADSTART_Msk);  //Start

}

void ADC1_Start() {

  ADC12_COMMON->CCR += 262144*Prescaler;

  while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};

  SET_BIT(ADC1->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADC2_Start() {

  ADC12_COMMON->CCR += 262144*Prescaler;

  while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};

  SET_BIT(ADC2->CR, ADC_CR_ADSTART_Msk);  //Start

}




void ResolutionSet(int Resolution) {

  //Sets Resolution

  CLEAR_BIT(ADC1->CFGR, ADC_CFGR_RES);

  switch (Resolution) {
    case 8:
      SET_BIT(ADC1->CFGR, ADC_CFGR_RES);
      break;
    case 10:
      SET_BIT(ADC1->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_1);
      break;
    case 12:
      SET_BIT(ADC1->CFGR, ADC_CFGR_RES_2 | ADC_CFGR_RES_1);
      break;
    case 14:
      SET_BIT(ADC1->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_2);
      break;
    default:
      break;
  };
}




void SystemCLCKInit(double ClockSpeedMHZ) {

#if defined(ARDUINO_GIGA)
  RCC->PLLCKSELR = 0x0200F022; //Divide 16mhz clock to 1
#elif defined(STM32H747xx)
  RCC->PLLCKSELR = 0x02017022; //Divide 24mhz clock to 1
#else
  #error Unsupported microcontroller, this library currently only works for STM32H747 based arduino boards.
#endif
int AdcPrescDivision = 1; //How much does clock get divided
ClockSpeedMHZ *= 2; //ADC always further divides clockspeed by 2, compensate

//Calculate proper prescaler if needed

if(128<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 256;
Prescaler = 11;
} else if(64<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 128;
Prescaler = 10;
} else if(32<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 64;
Prescaler = 9;
} else if(16<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 32;
Prescaler = 8;
} else if(12<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 16;
Prescaler = 7;
} else if(10<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 12;
Prescaler = 6;
} else if(8<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 10;
Prescaler = 5;
} else if(6<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 8;
Prescaler = 4;
} else if(4<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 6;
Prescaler = 3;
} else if(2<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 4;
Prescaler = 2;
} else if(1<1.2/ClockSpeedMHZ) {
AdcPrescDivision = 2;
Prescaler = 1;
};

  //Calculate dividor to use

  int dividor = ceil(150.0f / ClockSpeedMHZ / AdcPrescDivision);
  if (dividor>128) {
dividor = 128;
  };

  //Set generator speed, remain in 150-300mhz range as long as possible
  
  RCC->PLL2DIVR = 0x01010000;  //Sets the generator speed
  RCC->PLL2DIVR += dividor*512-512;
  RCC->PLL2DIVR += ceil(ClockSpeedMHZ*dividor*AdcPrescDivision-4);  //Sets the generator speed

  SET_BIT(RCC->CR, RCC_CR_PLL2ON); //Enable generator
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_DIVP2EN);  //Enable output


  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN_Msk);  //Enable ADC
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN); //Enable GPIOs

 
//Set boost mode so ADC can run faster
  
if (ClockSpeedMHZ>50) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST);
  SET_BIT(ADC2->CR, ADC_CR_BOOST);
} else if (ClockSpeedMHZ>25) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST_1);
  SET_BIT(ADC2->CR, ADC_CR_BOOST_1);
} else if (ClockSpeedMHZ>12.5) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST_0);
  SET_BIT(ADC2->CR, ADC_CR_BOOST_0);
}

  delay(100); //Make sure changes got applied
}





int CatchADC1Value() {

  while (!READ_REG(ADC1->ISR & ADC_ISR_EOC)) {}; //Wait for a new value if the latest one was already read
return(READ_REG(ADC1->DR)); //Return the new value

}

int CatchADC2Value() {

  while (!READ_REG(ADC2->ISR & ADC_ISR_EOC)) {}; //Wait for a new value if the latest one was already read
return(READ_REG(ADC2->DR)); //Return the new value

}

