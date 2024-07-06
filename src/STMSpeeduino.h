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
#include "DMAConfig.h"

void ADCInterleaved(int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ);
void ADCSimultaneous(int ADC1Channel, int ADC2Channel, int Resolution, double ClockSpeedMHZ, int SampleTime, int Samplenum);
void ADCBegin(ADC_TypeDef * ADC, int ADCChannel, int Resolution, bool Differential, double ClockSpeedMHZ, int SampleTime, int Samplenum);

int CatchADCValue(ADC_TypeDef * ADC, uint32_t Timeout);

void SystemCLCKInit(double ClockSpeedMHZ);

void ADC_Start(ADC_TypeDef * ADC);
void ADC_Stop(ADC_TypeDef * ADC);
void ADCChangeChannel(ADC_TypeDef * ADC, int AdcChannel);

void ADCSimultaneous_Start();
void ADCInterleaved_Start(int Resolution);

double GetADCFrequency();


int FastAnalogRead(int Pin);

void OPAMPCFG(int Gain);

void captureADC1values(int Size, uint16_t* BufferAddress);
void captureADC2values(int Size, uint16_t* BufferAddress);
void captureADC3values(int Size, uint16_t* BufferAddress);
void captureSimultaneousValues(int Size, uint16_t* Buffer1Address, uint16_t* Buffer2Address);
void captureInterleavedValues(int Size, uint16_t* BufferAddress);

void recaptureADC1values();
void recaptureADC2values();
void recaptureADC3values();
void recaptureInterleavedValues();
void recaptureSimultaneousValues();

bool TransferADC1Complete();
bool TransferADC2Complete();
bool TransferADC3Complete();
bool TransferInterleavedComplete();
bool TransferSimultaneousComplete();



#endif
