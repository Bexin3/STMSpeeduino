[![DOI](https://zenodo.org/badge/612708712.svg)](https://doi.org/10.5281/zenodo.15555644)

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

ADCBegin - Start one of the ADCs

ADCStart- Starts one of the ADCs

ADCStop - Stops one of the ADCs

ADCChangeChannel - Changes an ADC channel

FastAnalogRead - quickly read the channel with a relevant ADC

CatchADCValue - writes down the ADC value from latest conversion, and if it was already read, waits for next conversion to happen

OPAMPCFG - starts the operational amplifier, only supported when using Giga R1 Wifi.


DMA Functions; (Adcs have to be initiated, using the ones starting or restarting transfer will lead to the ADC being stopped after) 


captureADCvalues - Store a defined ammount of values into a buffer

captureSimultaneousValues - Store a defined ammount of values into two buffers one for each ADC

captureInterleavedValues - Store a defined ammount of values into a buffer using two ADCs 

recaptureADCvalues - Store values again using last settings

TransferADCComplete - Checks if DMA transfer is complete


Due to caching if you read buffer value while the program is running you may have to invalidate it
DMA can transfer up to 65535 values.
Using SDRAM using the default library will take away the control of clock speeds from the user as the clock will now be set up for it instead of for the ADC, however you can avoid this by running SDRAM from HCLK. I cant guarantee stability on giga as its 240mhz instead of 200 (The SDRAM should however be able to run up to 166mhz and the clock is divided by two, so only 120mhz), though it is working well for me so far. See [https://github.com/Bexin3/ArduinoCore-mbed-HCLK-ram/blob/main/libraries/Portenta_SDRAM/src/ram_internal.c](https://github.com/arduino/ArduinoCore-mbed/pull/995/files)
The only change is to the FMC_SDRAM_Clock_Config struct and definined clock in ram_internal.c and .h, and you dont have to recompile anything, if you go into default hardware libraries, changing this file will make it work.
