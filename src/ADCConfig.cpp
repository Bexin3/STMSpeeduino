
#include "ADCConfig.h"
#include "PinMappings.h"

bool ADC1Initialized = 0;
bool ADC2Initialized = 0;
bool ADC3Initialized = 0;
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

void ADC3Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

SystemCLCKInit(ClockSpeedMHZ);
ADC3_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum);
ADC3_Start();

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

  ADC1->PCSEL = 0xFFFFF;

  ADC1->SQR1 = 64 * AdcChannel;
  };





  ADC1->DIFSEL = 1048575 * Differential;  //Diffmode



  SET_BIT(ADC1->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  ResolutionSet(Resolution);  //Set resolution



  ADC1->SMPR1 = SampleTime * 153391689;  //Set sampletime
  ADC1->SMPR2 = SampleTime * 153391689;  //Set sampletime



  SET_BIT(ADC1->CR, ADC_CR_ADEN_Msk);                               //Enable ADC
  
    ADC1Initialized = 1;
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

  ADC2->PCSEL = 0xFFFFF;

  ADC2->SQR1 = 64 * AdcChannel;
  };



  ADC2->DIFSEL = 1048575 * Differential;  //Diffmode?



  SET_BIT(ADC2->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  Resolution2Set(Resolution);  //Set RESOLUTION



  ADC2->SMPR1 = SampleTime * 153391689;  //Divide
  ADC2->SMPR2 = SampleTime * 153391689;  //Divide


  SET_BIT(ADC2->CR, ADC_CR_ADEN_Msk);  
    
    ADC1Initialized = 2;

}


void ADC3_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {



  /***************ADC not Enabled yet********************/


  //Enable the voltage generator  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator

  CLEAR_BIT(ADC3->CR, ADC_CR_DEEPPWD);

  SET_BIT(ADC3->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator
  //ADC CALIBRATION-----------------------------------

  AdcChannel=ADC3PinRemap(AdcChannel);

  if(Differential) {
  SET_BIT(ADC3->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC3->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC3->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC3->CR & ADC_CR_ADCAL)) {};

  SET_BIT(ADC3->CFGR2, ADC_CFGR2_ROVSE);

  ADC3->CFGR2 += 65536 * Samplenum;




  if (Differential) {

  
  SET_BIT(ADC3->PCSEL, ADC_PCSEL_PCSEL_0 | ADC_PCSEL_PCSEL_1);

  ADC3->SQR1 = 64;

  } else {

  ADC3->PCSEL = 0xFFFFF;

  ADC3->SQR1 = 64 * AdcChannel;
  };



  ADC3->DIFSEL = 1048575 * Differential;  //Diffmode?



  SET_BIT(ADC3->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  Resolution2Set(Resolution);  //Set RESOLUTION



  ADC3->SMPR1 = SampleTime * 153391689;  //Divide
  ADC3->SMPR2 = SampleTime * 153391689;  //Divide


  SET_BIT(ADC3->CR, ADC_CR_ADEN_Msk);
    
    ADC3Initialized = 1;

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

  ADC12_COMMON->CCR += 262144*Prescaler; //

  while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};

  SET_BIT(ADC1->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADC2_Start() {

  ADC12_COMMON->CCR += 262144*Prescaler;

  while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};

  SET_BIT(ADC2->CR, ADC_CR_ADSTART_Msk);  //Start

}

void ADC3_Start() {

  ADC3_COMMON->CCR += 262144*Prescaler;

  while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {};

  SET_BIT(ADC3->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADC3_Stop() {
  
  SET_BIT(ADC3->CR, ADC_CR_ADSTP); //Clear result ready flag.
  
}

void ADC2_Stop() {
  
  SET_BIT(ADC2->CR, ADC_CR_ADSTP);
  
}

void ADC1_Stop() {
  
  SET_BIT(ADC1->CR, ADC_CR_ADSTP);
  
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


void Resolution3Set(int Resolution) {

  //Sets Resolution

  CLEAR_BIT(ADC3->CFGR, ADC_CFGR_RES);

  switch (Resolution) {
    case 8:
      SET_BIT(ADC3->CFGR, ADC_CFGR_RES);
      break;
    case 10:
      SET_BIT(ADC3->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_1);
      break;
    case 12:
      SET_BIT(ADC3->CFGR, ADC_CFGR_RES_2 | ADC_CFGR_RES_1);
      break;
    case 14:
      SET_BIT(ADC3->CFGR, ADC_CFGR_RES_0 | ADC_CFGR_RES_2);
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
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_ADC3EN); //Enable GPIOs and ADC3

 
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





int CatchADC1Value(uint32_t Timeout) {
    uint32_t InitMicros = micros();
    while (!READ_REG(ADC1->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC1->DR)); //Return the new value
}

int CatchADC2Value(uint32_t Timeout) {
    uint32_t InitMicros = micros();
    while (!READ_REG(ADC2->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC2->DR)); //Return the new value
}

int CatchADC3Value(uint32_t Timeout) {
    uint32_t InitMicros = micros();
    while (!READ_REG(ADC3->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC3->DR)); //Return the new value
}


int FastAnalogRead(int Pin) {
  switch (Pin) {
          
      case A0: if (ADC1Initialized) {return(ADC1InjectedRead(A0));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A0));}
               else {return(ADC1InjectedRead(A0));};
      case A1: if (ADC1Initialized) {return(ADC1InjectedRead(A1));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A1));}
               else {return(ADC1InjectedRead(A1));};
      case A2: if (ADC1Initialized) {return(ADC1InjectedRead(A2));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A2));}
               else {return(ADC1InjectedRead(A2));};
      case A3: if (ADC1Initialized) {return(ADC1InjectedRead(A3));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A3));}
               else {return(ADC1InjectedRead(A3));};
      case A4: if (ADC1Initialized) {return(ADC1InjectedRead(A4));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A4));}
               else {return(ADC1InjectedRead(A4));};
      case A5: if (ADC1Initialized) {return(ADC1InjectedRead(A5));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A5));}
               else if (ADC3Initialized) {return(ADC3InjectedRead(A5));}
               else {return(ADC1InjectedRead(A5));};
      case A6: if (ADC1Initialized) {return(ADC1InjectedRead(A6));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(A6));}
               else if (ADC3Initialized) {return(ADC3InjectedRead(A6));}
               else {return(ADC1InjectedRead(A6));};
      case A7: return(ADC1InjectedRead(A7));
      //A8-A11
      case 102: return(ADC3InjectedRead(102));
      case 103: return(ADC3InjectedRead(103));
      case 100: if (ADC1Initialized) {return(ADC1InjectedRead(100));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(100));}
                else {return(ADC1InjectedRead(100));};
      case 101: if (ADC1Initialized) {return(ADC1InjectedRead(101));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(101));}
                else {return(ADC1InjectedRead(101));};

      case DAC_0: if (ADC1Initialized) {return(ADC1InjectedRead(DAC_0));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(DAC_0));}
                else {return(ADC1InjectedRead(DAC_0));};
      case DAC_1: if (ADC1Initialized) {return(ADC1InjectedRead(DAC_1));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(DAC_1));}
                else {return(ADC1InjectedRead(DAC_1));};

      case 2: if (ADC1Initialized) {return(ADC1InjectedRead(2));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(2));}
                else {return(ADC1InjectedRead(2));};
      case 3: if (ADC1Initialized) {return(ADC1InjectedRead(3));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(3));}
                else {return(ADC1InjectedRead(3));};
      case 5: if (ADC1Initialized) {return(ADC1InjectedRead(5));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(5));}
                else {return(ADC1InjectedRead(5));};
      case 21: return(ADC3InjectedRead(21));
      case 56: if (ADC1Initialized) {return(ADC1InjectedRead(56));}
                else if (ADC2Initialized) {return(ADC2InjectedRead(56));}
                else {return(ADC1InjectedRead(56));};
      case 66: return(ADC1InjectedRead(66));
      case 73: if (ADC1Initialized) {return(ADC1InjectedRead(73));}
               else if (ADC2Initialized) {return(ADC2InjectedRead(73));}
               else if (ADC3Initialized) {return(ADC3InjectedRead(73));}
               else {return(ADC1InjectedRead(73));};
               
      default: return(-1);
  };
}

int ADC1InjectedRead(int ADCChannel) {
    if (!ADC1Initialized) {
        ADC1Begin();
    };
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};
    ADC1->JSQR = 512 * ADC1PinRemap(ADCChannel);
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {};
    uint32_t InitMicros = micros();
    SET_BIT(ADC1->CR, ADC_CR_JADSTART);
    while (!READ_REG(ADC1->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC1->JDR1)); //Return the new value
}

int ADC2InjectedRead(int ADCChannel) {
    if (!ADC2Initialized) {
        ADC2Begin();
    };
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};
    ADC2->JSQR = 512 * ADC2PinRemap(ADCChannel);
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {};
    uint32_t InitMicros = micros();
    SET_BIT(ADC2->CR, ADC_CR_JADSTART);
    while (!READ_REG(ADC2->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC2->JDR1)); //Return the new value
}

int ADC3InjectedRead(int ADCChannel) {
    if (!ADC3Initialized) {
        ADC3Begin();
    };
    while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {};
    ADC3->JSQR = 512 * ADC3PinRemap(ADCChannel);
    while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {};
    uint32_t InitMicros = micros();
    SET_BIT(ADC3->CR, ADC_CR_JADSTART);
    while (!READ_REG(ADC3->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC3->JDR1)); //Return the new value
}
