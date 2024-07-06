
#include "DMAConfig.h"
#include "ADCConfig.h"

int ADC1Size; //Size of buffer for ADC
int ADC2Size; //Size of buffer for ADC
int ADC3Size; //Size of buffer for ADC
int ADC12Size; //Size of buffer for ADC

uint16_t* Buffer1Add; //Address for the buffer
uint16_t* Buffer2Add; //Address for the buffer
uint16_t* Buffer3Add; //Address for the buffer



void captureADC1values(int Size, uint16_t* BufferAddress) {
    ADC_Stop(ADC1); //Stop ADC
    ADC1Size = Size; //Write down the ADC Size
    Buffer1Add = BufferAddress; //Write down the buffer address
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2); //Invalidate the cache so new values get read
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    ConfigDMA1_S5(Size, 0x40022040, BufferAddress, 1, 9); //Configure the relevant DMA stream as required
} 

void captureADC2values(int Size, uint16_t* BufferAddress) {
   ADC_Stop(ADC2); //Stop ADC
    ADC2Size = Size; //Write down the ADC Size
    Buffer2Add = BufferAddress; //Write down the buffer address
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2); //Invalidate the cache so new values get read
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    ConfigDMA1_S6(Size, 0x40022140, BufferAddress, 1, 10); //Configure the relevant DMA stream as required
}
void captureADC3values(int Size, uint16_t* BufferAddress) {
    ADC_Stop(ADC3); //Stop ADC
    ADC3Size = Size; //Write down the ADC Size
    Buffer3Add = BufferAddress; //Write down the buffer address
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2); //Invalidate the cache so new values get read
    SET_BIT(ADC3->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    ConfigDMA1_S7(Size, 0x58026040, BufferAddress, 1, 115); //Configure the relevant DMA stream as required
}

void captureInterleavedValues(int Size, uint16_t* BufferAddress) {
    ADC_Stop(ADC1); //Stop ADC
    ADC_Stop(ADC2); //Stop ADC
    ADC12Size = Size; //Write down the ADC Size
    Buffer1Add = BufferAddress; //Write down the buffer address
    SCB_InvalidateDCache_by_Addr(BufferAddress, Size*2); //Invalidate the cache so new values get read
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    SET_BIT(ADC12_COMMON->CCR, ADC_CCR_DAMDF_1); //Sets DMA for double ADC mode
    ConfigDMA1_S5(Size/2, 0x4002230C, BufferAddress, 2, 9); //Configure the relevant DMA stream as required
}

void captureSimultaneousValues(int Size, uint16_t* Buffer1Address, uint16_t* Buffer2Address) {
    ADC_Stop(ADC1); //Stop ADC
    ADC_Stop(ADC2); //Stop ADC
    Buffer1Add = Buffer1Address; //Write down the buffer address
    Buffer2Add = Buffer2Address; //Write down the buffer address
    ADC12Size = Size; //Write down the ADC Size
    SCB_InvalidateDCache_by_Addr(Buffer1Address, Size*2); //Invalidate the cache so new values get read
    SCB_InvalidateDCache_by_Addr(Buffer2Address, Size*2); //Invalidate the cache so new values get read
    SET_BIT(ADC1->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    SET_BIT(ADC2->CFGR, ADC_CFGR_DMNGT_0); //Set ADC to generate DMA requests
    ConfigDMA1_S5(Size, 0x40022040, Buffer1Address, 1, 9); //Configure the relevant DMA stream as required
    ConfigDMA1_S6(Size, 0x40022140, Buffer2Address, 1, 10); //Configure the relevant DMA stream as required
}





void ConfigDMA1_S5(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    //Clears Transfer flags
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5); 
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF5); 

    DMA1_Stream5->NDTR = Size; //Sets size of transfer
    DMA1_Stream5->PAR = InAddress; //Sets the Peripheral address to read from
    DMA1_Stream5->M0AR = (uint32_t) OutAddress; //Sets the address to write to

    DMA1_Stream5->CR &= 0 << 0; //Make sure the DMA is off

    DMA1_Stream5->CR = 0x30400; //Setup the DMA stream
    DMA1_Stream5->CR |= 0x2800 * TransferSize; //Set the size (0-8bits, 1-16, 2-32)
    DMAMUX1_Channel5->CCR = (DmaMUX<<0); //Set the DMAmux to allow the right peripheral to connect

    DMA1_Stream5->CR |= 1 << 0; //Enable the DMA stream
    
}

void ConfigDMA1_S6(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    //Clears Transfer flags
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF6); 
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF6);

    DMA1_Stream6->NDTR = Size; //Sets size of transfer
    DMA1_Stream6->PAR = InAddress; //Sets the Peripheral address to read from
    DMA1_Stream6->M0AR = (uint32_t) OutAddress; //Sets the address to write to

    DMA1_Stream6->CR &= 0 << 0; //Make sure the DMA is off

    DMA1_Stream6->CR = 0x30400; //Setup the DMA stream
    DMA1_Stream6->CR |= 0x2800 * TransferSize; //Set the size (0-8bits, 1-16, 2-32)
    DMAMUX1_Channel6->CCR = (DmaMUX<<0); //Set the DMAmux to allow the right peripheral to connect

    DMA1_Stream6->CR |= 1 << 0; //Enable the DMA stream
    
}

void ConfigDMA1_S7(uint16_t Size, int InAddress, uint16_t* OutAddress, int TransferSize, int DmaMUX) {
    
    //Clears Transfer flags
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF7);
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CTCIF7);

    DMA1_Stream7->NDTR = Size; //Sets size of transfer
    DMA1_Stream7->PAR = InAddress; //Sets the Peripheral address to read from
    DMA1_Stream7->M0AR = (uint32_t) OutAddress; //Sets the address to write to

    DMA1_Stream7->CR &= 0 << 0; //Make sure the DMA is off

    DMA1_Stream7->CR = 0x30400; //Setup the DMA stream
    DMA1_Stream7->CR |= 0x2800 * TransferSize; //Set the size (0-8bits, 1-16, 2-32)
    DMAMUX1_Channel7->CCR = (DmaMUX<<0); //Set the DMAmux to allow the right peripheral to connect

    DMA1_Stream7->CR |= 1 << 0; //Enable the DMA stream
    
}


void recaptureADC1values() {
    
    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTCIF5);  //Clear the transfer flags
    
    DMA1_Stream5->CR |= 1 << 0; //Enable the DMA stream
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC1Size*2);
}
void recaptureADC2values() {

    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF6 | DMA_HIFCR_CTCIF6);  //Clear the transfer flags
    
    DMA1_Stream6->CR |= 1 << 0; //Enable the DMA stream
    SCB_InvalidateDCache_by_Addr(Buffer2Add, ADC2Size*2); //Invalidate the cache
}

void recaptureADC3values() {

    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF7 | DMA_HIFCR_CTCIF7);  //Clear the transfer flags
    
    DMA1_Stream7->CR |= 1 << 0; //Enable the DMA stream
    SCB_InvalidateDCache_by_Addr(Buffer3Add, ADC3Size*2);  //Invalidate the cache
}

void recaptureInterleavedValues() {

    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTCIF5);  //Clear the transfer flags
    
    DMA1_Stream5->CR |= 1 << 0; //Enable the DMA stream
    
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC12Size*2);  //Invalidate the cache
}

void recaptureSimultaneousValues() {

    SET_BIT(DMA1->HIFCR, DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF6 | DMA_HIFCR_CTCIF6);  //Clear the transfer flags
    
    DMA1_Stream5->CR |= 1 << 0; //Enable the DMA stream
    DMA1_Stream6->CR |= 1 << 0; //Enable the DMA stream
    
    SCB_InvalidateDCache_by_Addr(Buffer1Add, ADC12Size*2);  //Invalidate the cache
    SCB_InvalidateDCache_by_Addr(Buffer2Add, ADC12Size*2);  //Invalidate the cache
}


bool TransferADC1Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF5)); //Check if transfer is complete
}

bool TransferADC2Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF6)); //Check if transfer is complete
}

bool TransferADC3Complete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF7)); //Check if transfer is complete
}

bool TransferInterleavedComplete() {
return(READ_BIT(DMA1->HISR, DMA_HISR_TCIF5)); //Check if transfer is complete
}

bool TransferSimultaneousComplete() {
    if (READ_BIT(DMA1->HISR, DMA_HISR_TCIF5) && READ_BIT(DMA1->HISR, DMA_HISR_TCIF6)) {
        return(1); //Check if transfer is complete
    } else {
        return(0);
    }
}



