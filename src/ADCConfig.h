#ifndef ADCConfig_h
#define ADCConfig_h

#include <Arduino.h>


void ADCInterleaved(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40);
void ADCSimultaneous(int ADC1Channel = A0, int ADC2Channel = A1, int Resolution = 16, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADCBegin(ADC_TypeDef* ADC, int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADCInitialize(ADC_TypeDef* ADC, int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADC_Init(ADC_TypeDef* ADC, int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADCEN(ADC_TypeDef* ADC);
void ADC_Start(ADC_TypeDef* ADC);
void ADC_Stop(ADC_TypeDef* ADC);
void ADCChangeChannel(ADC_TypeDef* ADC, int AdcChannel);
void ResolutionSet(ADC_TypeDef* ADC, int Resolution);
void SystemCLCKInit(double ClockSpeedMHZ);
int CatchADCValue(ADC_TypeDef* ADC, uint32_t Timeout = 0xFFFFFF);
int FastAnalogRead(int Pin, uint32_t Timeout = 0xFFFFFF);
int ADCInjectedRead(ADC_TypeDef* ADC, int ADCChannel, uint32_t Timeout);
double GetADCFrequency();
int GetADCNumber(ADC_TypeDef* ADC);




#endif
