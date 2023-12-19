
#include "DMAConfig.h"
#include "ADCConfig.h"

int ADC1Size;
int ADC2Size;
int ADC3Size;
int ADC12Size;

uint16_t* Buffer1Add;
uint16_t* Buffer2Add;
uint16_t* Buffer3Add;



void captureADC1values(int Size, uint16_t* BufferAddress) {
    ADC1_Stop();
    ADC1Size = Size;
    Buffer1Add = BufferAddress;
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2);
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0);
    ConfigDMA1_S5(Size, 0x40022040, BufferAddress, 1, 9);
    ADC1_Start();
}

void captureADC2values(int Size, uint16_t* BufferAddress) {
    ADC2_Stop();
    ADC2Size = Size;
    Buffer2Add = BufferAddress;
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2);
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0);
    ConfigDMA1_S6(Size, 0x40022140, BufferAddress, 1, 10);
    ADC2_Start();
}
void captureADC3values(int Size, uint16_t* BufferAddress) {
    ADC3_Stop();
    ADC3Size = Size;
    Buffer3Add = BufferAddress;
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2);
    SET_BIT(ADC3->CFGR, ADC_CFGR_DMNGT_0);
    ConfigDMA1_S7(Size, 0x58026040, BufferAddress, 1, 115);
    ADC3_Start();
}

void captureInterleavedValues(int Size, uint16_t* BufferAddress) {
    ADC1_Stop();
    ADC2_Stop();
    ADC12Size = Size;
    Buffer1Add = BufferAddress;
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2);
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0);
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0);
    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DAMDF_1);
    ConfigDMA1_S5(Size/2, 0x4002230C, BufferAddress, 2, 9);
    ADC1_Start();
    ADC2_Start();
}

void captureSimultaneousValues(int Size, uint16_t* Buffer1Address, uint16_t* Buffer2Address) {
    ADC1_Stop();
    ADC2_Stop();
    Buffer1Add = Buffer1Address;
    Buffer2Add = Buffer2Address;
    ADC12Size = Size;
    SCB_InvalidateDCache_by_Addr(Buffer1Address, Size*2);
    SCB_InvalidateDCache_by_Addr(Buffer2Address, Size*2);
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0);
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0);
    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DAMDF_1);
    ConfigDMA1_S5(Size, 0x4002230C, Buffer1Address, 1, 9);
    ConfigDMA1_S6(Size, 0x4002230C+2, Buffer2Address, 1, 9);
    ADC1_Start();
    ADC2_Start();

}





void ConfigDMA1_S5(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF5);

    DMA1_Stream5->NDTR = Size;
    DMA1_Stream5->PAR = InAddress;
    DMA1_Stream5->M0AR = (uint32_t) OutAddress;

    DMA1_Stream5->CR &= 0 << 0;

    DMA1_Stream5->CR = 0x30400;
    DMA1_Stream5->CR |= 0x2800 * TransferSize;
    DMAMUX1_Channel5->CCR = (DmaMUX<<0);

    //delay(6);

    DMA1_Stream5->CR |= 1 << 0;
    
}

void ConfigDMA1_S6(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF6);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF6);

    DMA1_Stream6->NDTR = Size;
    DMA1_Stream6->PAR = InAddress;
    DMA1_Stream6->M0AR = (uint32_t) OutAddress;

    DMA1_Stream6->CR &= 0 << 0;

    DMA1_Stream6->CR = 0x30400;
    DMA1_Stream6->CR |= 0x2800 * TransferSize;
    DMAMUX1_Channel6->CCR = (DmaMUX<<0);

    //delay(6);

    DMA1_Stream6->CR |= 1 << 0;
    
}

void ConfigDMA1_S7(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF7);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF7);

    DMA1_Stream7->NDTR = Size;
    DMA1_Stream7->PAR = InAddress;
    DMA1_Stream7->M0AR = (uint32_t) OutAddress;

    DMA1_Stream7->CR &= 0 << 0;

    DMA1_Stream7->CR = 0x30400;
    DMA1_Stream7->CR |= 0x2800 * TransferSize;
    DMAMUX1_Channel7->CCR = (DmaMUX<<0);

    //delay(6);

    DMA1_Stream7->CR |= 1 << 0;
    
}


void recaptureADC1values() {
    ADC1_Start();
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF5);
    DMA1_Stream5->CR |= 1 << 0;
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC1Size*2);
}
void recaptureADC2values() {
    ADC2_Start();
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF6);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF6);
    DMA1_Stream6->CR |= 1 << 0;
    SCB_InvalidateDCache_by_Addr(Buffer2Add, ADC2Size*2);
}

void recaptureADC3values() {
    ADC3_Start();
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF7);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF7);
    DMA1_Stream7->CR |= 1 << 0;
    SCB_InvalidateDCache_by_Addr(Buffer3Add, ADC3Size*2);
}

void recaptureInterleavedValues() {
    ADC1_Start();
    ADC2_Start();
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF5);
    DMA1_Stream5->CR |= 1 << 0;
    
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC12Size*2);
}

void recaptureSimultaneousValues() {
    ADC1_Start();
    ADC2_Start();
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF5);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF6);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF6);
    DMA1_Stream5->CR |= 1 << 0;
    DMA1_Stream6->CR |= 1 << 0;
    
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC12Size*2);
    SCB_InvalidateDCache_by_Addr(Buffer2Add, ADC12Size*2);
}

bool TransferADC1Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF5));
}

bool TransferADC2Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF6));
}

bool TransferADC3Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF7));
}

bool TransferInterleavedComplete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF5));
}

bool TransferSimultaneousComplete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF5));
}


