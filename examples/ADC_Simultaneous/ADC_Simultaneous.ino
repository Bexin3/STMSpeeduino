#include "STMSpeeduino.h"

int ADC1Channel = A0; //ADC 1 channel
int ADC2Channel = A1; //ADC 2 channel
int Resolution = 16; //8, 10, 12, 14, 16
double ClockSpeed = 40; //Clock speed in mhz, stable up to 40mhz, may decrease range further
int SampleTime = 0; //0 to 7
int Samplenum = 0; //Number of samples, is 1 more, 0 to 1023

long Val1;
long Val2;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
ADCSimultaneous(ADC1Channel, ADC2Channel, Resolution, ClockSpeed, SampleTime, Samplenum);

}

void loop() {
Val1 = CatchADCValue(ADC1);
Val2 = CatchADCValue(ADC2);
Serial.print("ADC1 value: ");
Serial.println(Val1);
Serial.print("ADC2 value: ");
Serial.println(Val2);
}
