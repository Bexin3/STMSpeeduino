#ifndef DMAConfig_h
#define DMAConfig_h

#include <Arduino.h>

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

void ConfigDMA1_S5(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX);
void ConfigDMA1_S6(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX);
void ConfigDMA1_S7(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX);


#endif
