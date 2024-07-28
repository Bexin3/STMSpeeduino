#ifndef DMAConfig_h
#define DMAConfig_h

#include <Arduino.h>

struct DMAStreamData {
  DMA_Stream_TypeDef* DMASt;
  DMAMUX_Channel_TypeDef* DMAMuxCh;
  long unsigned int DMA_CHT;
  long unsigned int DMA_CTC;
  long unsigned int DMA_TC;
};

struct ADC_DMAS {
  ADC_TypeDef* ADC;
  DMAStreamData AttachedStream;
  int StreamSize;
  uint16_t* BufferAddress;
  const int DMAMuxAdr;
  const int DataAddress;
  int PacketSize;
};

static DMAStreamData DMAS4 = { DMA1_Stream4, DMAMUX1_Channel4, DMA_HIFCR_CHTIF4, DMA_HIFCR_CTCIF4, DMA_HISR_TCIF4 };
static DMAStreamData DMAS5 = { DMA1_Stream5, DMAMUX1_Channel5, DMA_HIFCR_CHTIF5, DMA_HIFCR_CTCIF5, DMA_HISR_TCIF5 };
static DMAStreamData DMAS6 = { DMA1_Stream6, DMAMUX1_Channel6, DMA_HIFCR_CHTIF6, DMA_HIFCR_CTCIF6, DMA_HISR_TCIF6 };
static DMAStreamData DMAS7 = { DMA1_Stream7, DMAMUX1_Channel7, DMA_HIFCR_CHTIF7, DMA_HIFCR_CTCIF7, DMA_HISR_TCIF7 };

static ADC_DMAS ADC1DMA = { ADC1, {}, 0, 0, 9, 0x40022040, 1 };
static ADC_DMAS ADC2DMA = { ADC2, {}, 0, 0, 10, 0x40022140, 1 };
static ADC_DMAS ADC3DMA = { ADC3, {}, 0, 0, 115, 0x58026040, 1 };
static ADC_DMAS ADCInterDMA = { ADC1, {}, 0, 0, 9, 0x4002230C, 2 };  //If 0x4002230C activate DAMDF

void ConfigDMA(DMAStreamData DMAData, uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX);
void AttachADC_DMA(ADC_DMAS& ADC_DMA, uint16_t Size, uint16_t* BufferAddress, DMAStreamData DMAStream);
void recaptureADCvalues(ADC_DMAS ADC_DMA);
bool TransferADCComplete(ADC_DMAS ADC_DMA);
void UnattachDMA(ADC_DMAS ADC_DMA);


#endif
