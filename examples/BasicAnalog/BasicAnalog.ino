#include "STMSpeeduino.h"

int Channel = A0;
int Resolution = 16; //8, 10, 12, 14, 16
bool Differential = 0; //A10 has to be used as input positive on giga r1, A11 as negative
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz
int SampleTime = 0; //0 to 7
int Samplenum = 0; //Number of samples, is 1 more, 0 to 1023




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ADC1Begin(Channel, Resolution, Differential, ClockSpeed, SampleTime, Samplenum);
}

void loop() {
Serial.print("ADC1 value: ");
Serial.println(CatchADC1Value());
}
