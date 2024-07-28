#include "STMSpeeduino.h"
#include "SDRAM.h" //So values can be stored in SDRAM

const uint16_t ValuesToBuffer = 100;
uint16_t *FrameBuffer1 = (uint16_t *) 0x60000000;
uint16_t *FrameBuffer2 = (uint16_t *) 0x600F0000; 



void setup() {

SDRAM.begin();
ADCSimultaneous(); //Begin ADCs in simultaneous mode

AttachADC_DMA(ADC1DMA, ValuesToBuffer, FrameBuffer1, DMAS5);
AttachADC_DMA(ADC2DMA, ValuesToBuffer, FrameBuffer2, DMAS6);
ADC_Start(ADC1);
}

void loop() {
//Write out the values
while(!TransferADCComplete(ADC1DMA) || !TransferADCComplete(ADC2DMA)) {}; //Wait for the transfer to be complete
for (int i = 0; i < ValuesToBuffer; i++) {
Serial.print("ADC1 value ");
Serial.print(i);
Serial.print(": ");
Serial.println(FrameBuffer1[i]);
Serial.print("ADC2 value ");
Serial.print(i);
Serial.print(": ");
Serial.println(FrameBuffer2[i]);

};

recaptureADCvalues(ADC2DMA); //Start the capture again
recaptureADCvalues(ADC1DMA); //Start the capture again
ADC_Start(ADC1);

}
