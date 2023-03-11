#ifndef ADCConfig_h
#define ADCConfig_h

#include <Arduino.h>

void ADC_GetReady();



void ADCInterleaved(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40);
void ADCSimultaneous(int ADC1Channel = A0, int ADC2Channel = 1, int Resolution = 16, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADC1Begin(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADC2Begin(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);

int CatchADC1Value();
int CatchADC2Value();

void ADC1_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADC2_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void SystemCLCKInit(double ClockSpeedMHZ);
void ResolutionSet(int Resolution);
void Resolution2Set(int Resolution);
void ADC2_Start();
void ADC1_Start();
void ADCSimultaneous_Start();
void ADCInterleaved_Start(int Resolution);


#endif
