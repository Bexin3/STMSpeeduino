#ifndef STMSpeeduino_h
#define STMSpeeduino_h



#if defined(ARDUINO_GIGA)
#define A10 100
#define A11 101
#define A8 102
#define A9 103
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
void ADC3Begin(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum);

int CatchADC1Value(uint32_t Timeout);
int CatchADC2Value(uint32_t Timeout);
int CatchADC3Value(uint32_t Timeout);

void SystemCLCKInit(double ClockSpeedMHZ);
void ADC3_Start();
void ADC2_Start();
void ADC1_Start();
void ADC3_Stop();
void ADC2_Stop();
void ADC1_Stop();
void ADCSimultaneous_Start();
void ADCInterleaved_Start(int Resolution);


void OPAMPCFG(int Gain);



#endif
