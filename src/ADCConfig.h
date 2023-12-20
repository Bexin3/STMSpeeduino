#ifndef ADCConfig_h
#define ADCConfig_h

#include <Arduino.h>


void ADCInterleaved(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40);
void ADCSimultaneous(int ADC1Channel = A0, int ADC2Channel = A1, int Resolution = 16, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADC1Begin(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADC2Begin(int ADCChannel = A0, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);
void ADC3Begin(int ADCChannel = A5, int Resolution = 16, bool Differential = 0, double ClockSpeedMHZ = 40, int SampleTime = 0, int Samplenum = 0);

int CatchADC1Value(uint32_t Timeout = 0xFFFFFF);
int CatchADC2Value(uint32_t Timeout = 0xFFFFFF);
int CatchADC3Value(uint32_t Timeout = 0xFFFFFF);

void ADC1_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADC2_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADC3_Init(int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum);
void ADCInitialize(ADC_TypeDef * ADC, int AdcChannel, int Resolution, bool Differential, int SampleTime, int Samplenum)
void SystemCLCKInit(double ClockSpeedMHZ);
void ResolutionSet(int Resolution);
void Resolution2Set(int Resolution);
void Resolution3Set(int Resolution);
void ADC3_Start();
void ADC2_Start();
void ADC1_Start();
void ADC3_Stop();
void ADC2_Stop();
void ADC1_Stop();
void ADC3ChangeChannel(int AdcChannel);
void ADC2ChangeChannel(int AdcChannel);
void ADC1ChangeChannel(int AdcChannel);
void ADC1EN();
void ADC2EN();
void ADC3EN();
void ADCSimultaneousConfig();
void ADCInterleavedConfig(int Resolution);

int ADC1InjectedRead(int ADCChannel);
int ADC2InjectedRead(int ADCChannel);
int ADC3InjectedRead(int ADCChannel);
int FastAnalogRead(int Pin);

#endif
