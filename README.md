Compatible with Giga R1 wifi, Portenta h7 and possibly other stm32h747 boards. You can find the list of supported pins on GIGAR1 in pinmappings.h file in src.

As of now this library is still in development, as well as its doccumentation. The planned features can be found in Issues.

Highest possible clock speed without compromising range is about 40mhz but this depends on the pins.


Ammount of clock cycles different resolutions take up:

16bits - 10

14bits - 9

12bits - 8

10bits - 7

8bits  - 6


Function descriptions - 

ADCInterleaved - Starts both adc so they meassure one channel, in which they take turns, allows for double the speed of using just one channel, but the two channels dont tend to be perfectly calibrated

ADCSimultaneous - Starts both ADCs so they read two different channels exactly in phase

ADC1/2/3Begin - Start one of the ADCs

ADC1/2/3Stop - Stops one of the ADCs

CatchADC1/2/3Value - writes down the ADC value from latest conversion, and if it was already read, waits for next conversion to happen

OPAMPCFG - starts the operational amplifier, only supported when using Giga R1 Wifi.
