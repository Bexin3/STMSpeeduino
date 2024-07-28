#include "STMSpeeduino.h"

//Use A2 as input, A0 will be amplified
int Resolution = 16; //8, 10, 12, 14, 16
bool Differential = 0; //A10 has to be used as input positive on giga r1, A11 as negative
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz
int SampleTime = 0; //0 to 7
int Samplenum = 0; //Number of samples, is 1 more, 0 to 1023
int Gain = 2; //2 to 16



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
OPAMPCFG(Gain);
ADCBegin(ADC1, A0, Resolution, Differential, ClockSpeed, SampleTime, Samplenum);

}

void loop() {
Serial.print("ADC1 value: ");
Serial.println(CatchADCValue(ADC1));
}
