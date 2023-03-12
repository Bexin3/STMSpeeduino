Compatible with Giga R1 wifi, Portenta h7 and possibly other stm32h747 boards.


As of now this library is still in development, as well as its doccumentation, I plan to add ADC 3 usage possability, and direct memory access, as well as other than analog features.


Highest possible clock speed without compromising range is abiut 40mhz.
For now with unfinished documentations, look into examples to see how to use functions, and I also will be releasing an osciloscope library based on this soon.


Ammount of clock cycles different resolutions take up:

16bits - 10

14bits - 9

12bits - 8

10bits - 7

8bits  - 6


Function descriptions - 

ADCInterleaved - Starts both adc so they meassure one channel, in which they take turns, allows for double the speed of using just one channel, but the two channels dont tend to be perfectly calibrated

ADCSimultaneous - Starts both ADCs so they read two different channels exactly in phase

ADC1/2Begin - Start one of the ADCs

CatchADC1/2Value - writes down the ADC value from latest conversion, and if it was already read, waits for next conversion to happen

OPAMPCFG - starts the operational amplifier, only supported when using Giga R1 Wifi.
