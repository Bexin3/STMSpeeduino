#include "STMSpeeduino.h"

int ADCChannel = A0;
int Resolution = 16; //8, 10, 12, 14, 16
bool Differential = 0; //A10 has to be used as input positive on giga r1, A11 as negative
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ADCInterleaved();

}

void loop() {
Serial.print("ADC value: ");
Serial.println(CatchADCValue(ADC1));
Serial.print("ADC value: ");
Serial.println(CatchADCValue(ADC2));
}
