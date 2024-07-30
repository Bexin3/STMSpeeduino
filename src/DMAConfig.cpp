
#include "DMAConfig.h"
#include "ADCConfig.h"



void ConfigDMA(DMAStreamData DMAData, uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {

  //Clears Transfer flags
  SET_BIT(DMA1->HIFCR, DMAData.DMA_CHT);
  SET_BIT(DMA1->HIFCR, DMAData.DMA_CTC);

  DMAData.DMASt->NDTR = Size;                  //Sets size of transfer
  DMAData.DMASt->PAR = InAddress;              //Sets the Peripheral address to read from
  DMAData.DMASt->M0AR = (uint32_t)OutAddress;  //Sets the address to write to

  DMAData.DMASt->CR &= 0 << 0;  //Make sure the DMA is off

  DMAData.DMASt->CR = 0x30400;                 //Setup the DMA stream
  DMAData.DMASt->CR |= 0x2800 * TransferSize;  //Set the size (0-8bits, 1-16, 2-32)
  DMAData.DMAMuxCh->CCR = (DmaMUX << 0);       //Set the DMAmux to allow the right peripheral to connect

  DMAData.DMASt->CR |= 1 << 0;  //Enable the DMA stream
}
//Broken gp
void AttachADC_DMA(ADC_DMAS& ADC_DMA, uint16_t Size, uint16_t* BufferAddress, DMAStreamData DMAStream) {
  ADC_Stop(ADC_DMA.ADC);  //Stop ADC
  ADC_DMA.AttachedStream = DMAStream;
  ADC_DMA.StreamSize = Size;
  ADC_DMA.BufferAddress = (uint16_t*)BufferAddress;
  SCB_InvalidateDCache_by_Addr(BufferAddress, Size * 2);  //Invalidate the cache so new values get read
  SET_BIT(ADC_DMA.ADC->CFGR, ADC_CFGR_DMNGT_0);
  if (ADC_DMA.DataAddress == ADCInterDMA.DataAddress) {
    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DAMDF_1);  //Sets DMA for double ADC mode
    ConfigDMA(ADC_DMA.AttachedStream, ADC_DMA.StreamSize / 2, ADC_DMA.DataAddress, ADC_DMA.BufferAddress, ADC_DMA.PacketSize, ADC_DMA.DMAMuxAdr);
  } else {
    ConfigDMA(ADC_DMA.AttachedStream, ADC_DMA.StreamSize, ADC_DMA.DataAddress, ADC_DMA.BufferAddress, ADC_DMA.PacketSize, ADC_DMA.DMAMuxAdr);
  };
}



void recaptureADCvalues(ADC_DMAS ADC_DMA) {

  ADC_Start(ADC_DMA.ADC);
  SET_BIT(DMA1->HIFCR, ADC_DMA.AttachedStream.DMA_CHT | ADC_DMA.AttachedStream.DMA_CTC);  //Clear the transfer flags

  ADC_DMA.AttachedStream.DMASt->CR |= 1 << 0;  //Enable the DMA stream
  SCB_InvalidateDCache_by_Addr(ADC_DMA.BufferAddress, ADC_DMA.StreamSize * 2);
}



bool TransferADCComplete(ADC_DMAS ADC_DMA) {
  return (READ_BIT(DMA1->HISR, ADC_DMA.AttachedStream.DMA_TC));  //Check if transfer is complete
}


void UnattachDMA(ADC_DMAS ADC_DMA) {
  ADC_Stop(ADC_DMA.ADC);
  CLEAR_BIT(ADC_DMA.ADC->CFGR, ADC_CFGR_DMNGT_0);
  if (ADC_DMA.DataAddress == ADCInterDMA.DataAddress) {
    CLEAR_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0);        //Set ADC to generate DMA requests
    CLEAR_BIT(ADC12_COMMON->CCR, ADC_CCR_DAMDF_1);  //Sets DMA for double ADC mode
  }
  ADC_Start(ADC_DMA.ADC);
}
