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
void ADC3ChangeChannel(int AdcChannel);
void ADC2ChangeChannel(int AdcChannel);
void ADC1ChangeChannel(int AdcChannel);
void ADCSimultaneous_Start();
void ADCInterleaved_Start(int Resolution);

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
