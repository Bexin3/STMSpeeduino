#include "STMSpeeduino.h"


const uint16_t ValuesToBuffer = 100;
uint16_t FrameBuffer1[ValuesToBuffer];



void setup() {


ADCSimultaneous(); //Begin ADCs in simultaneous mode

captureSimultaneousValues(ValuesToBuffer, FrameBuffer1, FrameBuffer2);
  
}

void loop() {
//Write out the values
while(!TransferSimultaneousComplete()) {}; //Wait for the transfer to be complete
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

recaptureSimultaneousValues(); //Start the capture again


}
