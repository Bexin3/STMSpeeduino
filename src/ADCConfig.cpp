
#include "ADCConfig.h"
#include "PinMappings.h"

bool ADC1Initialized = 0; //Stores information on if ADC1 is Initialized
bool ADC2Initialized = 0; //Stores information on if ADC2 is Initialized
bool ADC3Initialized = 0; //Stores information on if ADC3 is Initialized
int Prescaler = 0; //Stores the Calculated Prescaler value
bool ClockInitialized = 0; //Stores if clock is initialized

void ADCInterleaved(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ) {

if (!ClockInitialized) {SystemCLCKInit(ClockSpeedMHZ);}; //Initiate System clock
ADC1_Init(ADCChannel, Resolution, Differential, 0, 0); //Initiate ADC1
ADC2_Init(ADCChannel, Resolution, Differential, 0, 0); //Initiate ADC2
ADCInterleavedConfig(Resolution); //Configure Interleaved mode
    ADC1EN(); //Enable ADC1
    ADC2EN(); //Enable ADC2
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {}; //Waits for ADC1 to be ready
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {}; //Waits for ADC2 to be ready
    ADC1_Start(); //Starts the conversions

} //Initiates and starts ADC1 and ADC2 in Interleaved modes.

void ADCSimultaneous(int ADC1Channel, int ADC2Channel, int Resolution, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

if (!ClockInitialized) {SystemCLCKInit(ClockSpeedMHZ);}; //Initiate System clock
ADC1_Init(ADC1Channel, Resolution, 0, SampleTime, Samplenum); //Initiate ADC1
ADC2_Init(ADC2Channel, Resolution, 0, SampleTime, Samplenum); //Initiate ADC2
ADCSimultaneousConfig(); //Configure Simultaneous mode
    ADC1EN(); //Enable ADC1
    ADC2EN(); //Enable ADC2
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {}; //Waits for ADC1 to be ready
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {}; //Waits for ADC2 to be ready
    ADC1_Start(); //Starts the conversions

} //Initiates and starts ADC1 and ADC2 in Simultaneous modes.


void ADC1Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

if (!ClockInitialized) {SystemCLCKInit(ClockSpeedMHZ);}; //Initiate System clock
ADC1_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum); //Initiate ADC1
ADC1EN(); //Enable ADC1
ADC1_Start(); //Start ADC1 conversions
    

} //Initiates and starts ADC1

void ADC2Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

if (!ClockInitialized) {SystemCLCKInit(ClockSpeedMHZ);}; //Initiate System clock
ADC2_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum); //Initiate ADC2
ADC2EN(); //Enable ADC2
ADC2_Start(); //Start ADC2 conversions

} //Initiates and starts ADC2

void ADC3Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum) {

if (!ClockInitialized) {SystemCLCKInit(ClockSpeedMHZ);}; //Initiate System clock
ADC3_Init(ADCChannel, Resolution, Differential, SampleTime, Samplenum); //Initiate ADC3
ADC3EN(); //Enable ADC3
ADC3_Start(); //Start ADC3 conversions

} //Initiates and starts ADC3





void ADC1_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {


  //GPIOA PORT 1------------------------------------

  

  /***************ADC not Enabled yet********************/

  CLEAR_BIT(ADC1->CR, ADC_CR_DEEPPWD);     //Wake up from deep sleep

  SET_BIT(ADC1->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator


  AdcChannel=ADC1PinRemap(AdcChannel);     //Get actual channel number

  //ADC CALIBRATION

  if(Differential) {
  SET_BIT(ADC1->CR, ADC_CR_ADCALDIF); 
  };
  SET_BIT(ADC1->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC1->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC1->CR & ADC_CR_ADCAL)) {};

  
  SET_BIT(ADC1->CFGR2, ADC_CFGR2_ROVSE); //Set oversampling

  
  ADC1->CFGR2 += 65536 * Samplenum; //Set number of samples




  ADC1->PCSEL = 0xFFFFF; //Enable all channels

  ADC1->SQR1 = 64 * AdcChannel;   //Select channel



  ADC1->DIFSEL = 1048575 * Differential;  //Enable differential mode if needed



  SET_BIT(ADC1->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  ResolutionSet(Resolution);  //Set resolution



  ADC1->SMPR1 = SampleTime;  //Set sampletime

  
  ADC1Initialized = 1;
}


void ADC2_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {



  /***************ADC not Enabled yet********************/


  //Enable the voltage generator  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator

  CLEAR_BIT(ADC2->CR, ADC_CR_DEEPPWD);

  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator


  AdcChannel=ADC2PinRemap(AdcChannel); //Get actual channel number

  //ADC CALIBRATION-----------------------------------
  if(Differential) {
  SET_BIT(ADC2->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC2->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC2->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC2->CR & ADC_CR_ADCAL)) {};

  SET_BIT(ADC2->CFGR2, ADC_CFGR2_ROVSE); //Allow Oversampling

  ADC2->CFGR2 += 65536 * Samplenum; //Set number of samples



  ADC2->PCSEL = 0xFFFFF; //Enable all channels

  ADC2->SQR1 = 64 * AdcChannel; //Select a channel




  ADC2->DIFSEL = 1048575 * Differential;  //Enable differential mode if needed



  SET_BIT(ADC2->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  Resolution2Set(Resolution);  //Set RESOLUTION



  ADC2->SMPR1 = SampleTime * 153391689;  //Divide
  ADC2->SMPR2 = SampleTime * 153391689;  //Divide




    

    
    ADC2Initialized = 1;

}


void ADC3_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum) {



  /***************ADC not Enabled yet********************/


  //Enable the voltage generator  SET_BIT(ADC2->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator

  CLEAR_BIT(ADC3->CR, ADC_CR_DEEPPWD);

  SET_BIT(ADC3->CR, ADC_CR_ADVREGEN_Msk);  //Enable the voltage generator


  AdcChannel=ADC3PinRemap(AdcChannel); //Get actual channel id

  //ADC CALIBRATION-----------------------------------
  if(Differential) {
  SET_BIT(ADC3->CR, ADC_CR_ADCALDIF);
  };
  SET_BIT(ADC3->CR, ADC_CR_ADCALLIN);
  SET_BIT(ADC3->CR, ADC_CR_ADCAL);
  while (READ_REG(ADC3->CR & ADC_CR_ADCAL)) {};

  SET_BIT(ADC3->CFGR2, ADC_CFGR2_ROVSE); //Allow oversampling

  ADC3->CFGR2 += 65536 * Samplenum; //Set number of samples




  ADC3->PCSEL = 0xFFFFF; //Enable all ADC Channels

  ADC3->SQR1 = 64 * AdcChannel; //Select ADC Channel
 



  ADC3->DIFSEL = 1048575 * Differential;  //Enable differential mode if needed



  SET_BIT(ADC3->CFGR, ADC_CFGR_OVRMOD_Msk | ADC_CFGR_CONT_Msk | ADC_CFGR_JQM | ADC_CFGR_JDISCEN);  //Enable Continuous mode, Always overwrite data

  Resolution2Set(Resolution);  //Set RESOLUTION



  ADC3->SMPR1 = SampleTime * 153391689;  //Divide
  ADC3->SMPR2 = SampleTime * 153391689;  //Divide




    
    ADC3Initialized = 1;

}






void ADCInterleavedConfig(int Resolution) {


    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DUAL_0 | ADC_CCR_DUAL_1); //Configures Interleaved mode

}


void ADCSimultaneousConfig() {
    
    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DUAL_0); //Configure Simultaneous mode
    
}
    
void ADC1EN() {
    ADC12_COMMON->CCR |= Prescaler << 18; //Set Prescaler value
        SET_BIT(ADC1->CR, ADC_CR_ADEN_Msk); //Enable
}

void ADC2EN() {
    ADC12_COMMON->CCR |= Prescaler << 18; //Set Prescaler value
        SET_BIT(ADC2->CR, ADC_CR_ADEN_Msk); //Enable
}

void ADC3EN() {
    ADC3_COMMON->CCR |= Prescaler << 18; //Set Prescaler value
        SET_BIT(ADC3->CR, ADC_CR_ADEN_Msk); //Enable
}

void ADC1_Start() {



  while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready to start

  SET_BIT(ADC1->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADC2_Start() {



  while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready to start

  SET_BIT(ADC2->CR, ADC_CR_ADSTART_Msk);  //Start

}

void ADC3_Start() {



  while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready to start

  SET_BIT(ADC3->CR, ADC_CR_ADSTART_Msk);  //Start

}


void ADC3_Stop() {
  
  SET_BIT(ADC3->CR, ADC_CR_ADSTP); //Stop the ADC
  while (READ_REG(ADC3->CR & ADC_CR_ADSTP)) {}; //Wait for ADC to stop

}

void ADC2_Stop() {
  
  SET_BIT(ADC2->CR, ADC_CR_ADSTP); //Stop the ADC
  while (READ_REG(ADC2->CR & ADC_CR_ADSTP)) {}; //Wait for ADC to stop
  
}

void ADC1_Stop() {
  
  SET_BIT(ADC1->CR, ADC_CR_ADSTP); //Stop the ADC
  while (READ_REG(ADC1->CR & ADC_CR_ADSTP)) {}; //Wait for ADC to stop

}


void ADC1ChangeChannel(int AdcChannel) {
    bool ADActive = READ_REG(ADC1->CR & ADC_CR_ADSTART); //Check if ADC is active
    if(ADActive) {ADC1_Stop();}; //Stop the ADC if active
    
    while (READ_REG(ADC1->CR & ADC_CR_ADSTP) || READ_REG(ADC1->CR & ADC_CR_JADSTART)) {}; //Wait for ADC to stop
    ADC1->SQR1 = 64 * ADC1PinRemap(AdcChannel); //Set ADC Channel
    
    if(ADActive) {ADC1_Start();}; //If ADC was initially active turn it back on
}

void ADC2ChangeChannel(int AdcChannel) {
    bool ADActive = READ_REG(ADC2->CR & ADC_CR_ADSTART); //Check if ADC is active
    if(ADActive) {ADC2_Stop();}; //Stop the ADC if active
    
    while (READ_REG(ADC2->CR & ADC_CR_ADSTP) || READ_REG(ADC2->CR & ADC_CR_JADSTART)) {}; //Wait for ADC to stop
    ADC2->SQR1 = 64 * ADC2PinRemap(AdcChannel); //Set ADC Channel
    
    if(ADActive) {ADC2_Start();}; //If ADC was initially active turn it back on
}

void ADC3ChangeChannel(int AdcChannel) {
    bool ADActive = READ_REG(ADC3->CR & ADC_CR_ADSTART); //Check if ADC is active
    if(ADActive) {ADC3_Stop();};  //Stop the ADC if active
    
    while (READ_REG(ADC3->CR & ADC_CR_ADSTP) || READ_REG(ADC3->CR & ADC_CR_JADSTART)) {}; //Wait for ADC to stop
    ADC3->SQR1 = 64 * ADC3PinRemap(AdcChannel); //Set ADC Channel
    
    if(ADActive) {ADC3_Start();}; //If ADC was initially active turn it back on
}


void ResolutionSet(int Resolution) {

  //Sets Resolution for the ADC

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



void Resolution2Set(int Resolution) {

  //Sets Resolution for the ADC

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


void Resolution3Set(int Resolution) {

  //Sets Resolution for the ADC

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
  RCC->PLL2DIVR += dividor*512-512; //Calculation
  RCC->PLL2DIVR += ceil(ClockSpeedMHZ*dividor*AdcPrescDivision-4);  //Sets the generator speed

  SET_BIT(RCC->CR, RCC_CR_PLL2ON); //Enable generator
  SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_DIVP2EN);  //Enable output


  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ADC12EN_Msk | RCC_AHB1ENR_DMA1EN);  //Enable ADC 1 and 2 and DMA1
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN | RCC_AHB4ENR_GPIOBEN | RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_ADC3EN); //Enable GPIOs and ADC3

 
//Set boost mode so ADC can run faster
  
if (ClockSpeedMHZ>50) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST);
  SET_BIT(ADC2->CR, ADC_CR_BOOST);
  SET_BIT(ADC3->CR, ADC_CR_BOOST);
} else if (ClockSpeedMHZ>25) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST_1);
  SET_BIT(ADC2->CR, ADC_CR_BOOST_1);
  SET_BIT(ADC3->CR, ADC_CR_BOOST_0);
} else if (ClockSpeedMHZ>12.5) {
  SET_BIT(ADC1->CR, ADC_CR_BOOST_0);
  SET_BIT(ADC2->CR, ADC_CR_BOOST_0);
  SET_BIT(ADC3->CR, ADC_CR_BOOST_0);
}


}





int CatchADC1Value(uint32_t Timeout) {
    uint32_t InitMicros = micros(); //Capture current time
    while (!READ_REG(ADC1->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC1->DR)); //Return the new value
}

int CatchADC2Value(uint32_t Timeout) {
    uint32_t InitMicros = micros(); //Capture current time
    while (!READ_REG(ADC2->ISR & ADC_ISR_EOC) && (micros() < (InitMicros + Timeout))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC2->DR)); //Return the new value
}

int CatchADC3Value(uint32_t Timeout) {
    uint32_t InitMicros = micros(); //Capture current time
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
} //Quickly read a pin from the first initiated ADC using injected conversion - not stopping usual conversion, or Initiate first in order ADC and read.

int ADC1InjectedRead(int ADCChannel) {
    if (!ADC1Initialized) { 
        ADC1Begin();
    }; //Begin ADC if not initialized
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    ADC1->JSQR = 512 * ADC1PinRemap(ADCChannel); //Set the injected pin to ID
    while (!READ_REG(ADC1->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    uint32_t InitMicros = micros(); //Capture current time
    SET_BIT(ADC1->CR, ADC_CR_JADSTART); //Start the conversion
    while (!READ_REG(ADC1->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC1->JDR1)); //Return the new value
}

int ADC2InjectedRead(int ADCChannel) {
    if (!ADC2Initialized) {
        ADC2Begin();
    }; //Begin ADC if not initialized
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    ADC2->JSQR = 512 * ADC2PinRemap(ADCChannel); //Set the injected pin to ID
    while (!READ_REG(ADC2->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    uint32_t InitMicros = micros(); //Capture current time
    SET_BIT(ADC2->CR, ADC_CR_JADSTART); //Start the conversion
    while (!READ_REG(ADC2->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC2->JDR1)); //Return the new value
}

int ADC3InjectedRead(int ADCChannel) {
    if (!ADC3Initialized) {
        ADC3Begin();
    }; //Begin ADC if not initialized
    while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    ADC3->JSQR = 512 * ADC3PinRemap(ADCChannel); //Set the injected pin to ID
    while (!READ_REG(ADC3->ISR & ADC_ISR_ADRDY)) {}; //Wait for ADC to be ready
    uint32_t InitMicros = micros(); //Capture current time
    SET_BIT(ADC3->CR, ADC_CR_JADSTART); //Start the conversion
    while (!READ_REG(ADC3->ISR & ADC_ISR_JEOC) && (micros() < (0xFFF + InitMicros))) {}; //Wait for a new value if the latest one was already read
    return(READ_REG(ADC3->JDR1)); //Return the new value
}
