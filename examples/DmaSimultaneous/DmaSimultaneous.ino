#include "STMSpeeduino.h"
#include "SDRAM.h" //So values can be stored in SDRAM

int ValuesToBuffer = 100
uint16_t *FrameBuffer1 = (uint16_t *) 0x60000000;
uint16_t *FrameBuffer2 = (uint16_t *) 0x600F0000; 



void setup() {

ADCSimultaneous(); //Begin ADCs in simultaneous mode

captureSimultaneousValues(ValuesToBuffer, FrameBuffer1, FrameBuffer2);
  
}

void loop() {
//Write out the values
for (int i = 0; i < ValuesToBuffer; i++) {
Serial.print("ADC1 value ");
Serial.print(i);
Serial.print(": ");
Serial.println(_fb[i]);
Serial.print("ADC2 value ");
Serial.print(i);
Serial.print(": ");
Serial.println(_fb[i]);

};

recaptureSimultaneousValues(); //Start the capture again
delay(100); //Wait 0.1s

}

