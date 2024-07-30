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

int FastAnalogRead(int Pin, uint32_t Timeout);

void OPAMPCFG(int Gain);

void AttachADC_DMA(ADC_DMAS& ADC_DMA, uint16_t Size, uint16_t* BufferAddress, DMAStreamData DMAStream);
void recaptureADCvalues(ADC_DMAS ADC_DMA);
bool TransferADCComplete(ADC_DMAS ADC_DMA);
void UnattachDMA(ADC_DMAS ADC_DMA);


#endif
