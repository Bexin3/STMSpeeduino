Compatible with Giga R1 wifi, Portenta h7 and possibly other stm32h747 boards. You can find the list of supported pins on GIGAR1 in pinmappings.cpp file in src.

As of now this library is still in development, The planned features can be found in Issues.

Highest possible clock speed without compromising range is about 40mhz but this depends on the pins to be read.


Ammount of clock cycles different resolutions take up:

16bits - 10

14bits - 9

12bits - 8

10bits - 7

8bits  - 6


Function descriptions - 

ADCInterleaved - Starts both adc so they meassure one channel, in which they take turns, allows for double the speed of using just one channel, but the two channels dont tend to be perfectly calibrated

ADCSimultaneous - Starts both ADCs so they read two different channels exactly in phase

ADC1/2/3 Begin - Start one of the ADCs

ADC1/2/3 Start- Starts one of the ADCs

ADC1/2/3 Stop - Stops one of the ADCs

ADC1/2/3ChangeChannel - Changes an ADC channel

FastAnalogRead - quickly read the channel with a relevant ADC

CatchADC1/2/3 Value - writes down the ADC value from latest conversion, and if it was already read, waits for next conversion to happen

OPAMPCFG - starts the operational amplifier, only supported when using Giga R1 Wifi.


DMA Functions; ((Adcs have to be initiated)


captureADC1/2/3values - Store a defined ammount of values into a buffer

captureSimultaneousValues - Store a defined ammount of values into two buffers one for each ADC

captureInterleavedValues - Store a defined ammount of values into a buffer using two ADCs 

recaptureADC1/2/3values - Store values again using last settings

recaptureInterleaved/SimultaneousValues - Store values again using last settings

TransferADC1/2/3/Interleaved/SimultaneousComplete - Checks if DMA transfer is complete


Due to caching if you read buffer value while the program is running you may have to invalidate it
DMA can transfer up to 65535 values.
