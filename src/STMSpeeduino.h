#ifndef STMSpeeduino_h
#define STMSpeeduino_h



#if defined(ARDUINO_GIGA)
#define A10 100
#define A11 101
#elif defined(ARDUINO_PORTENTA_H7)

#endif

#include <Arduino.h>
#include "ADCConfig.h"
#include "Opamp.h"
#include "PinMappings.h"

void ADC_GetReady();
void ADCInterleaved(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ);
void ADCSimultaneous(int ADC1Channel, int ADC2Channel, int Resolution, double ClockSpeedMHZ, int SampleTime, int Samplenum);
void ADC1Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum);
void ADC2Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum);

int CatchADC1Value();
int CatchADC2Value();

void SystemCLCKInit(double ClockSpeedMHZ);
void ADC2_Start();
void ADC1_Start();
void ADC2_Stop();
void ADC1_Stop();
void ADCSimultaneous_Start();
void ADCInterleaved_Start(int Resolution);


void OPAMPCFG(int Gain);



#endif
