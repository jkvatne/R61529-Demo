
# IPS LCD R61529 FT6236 Arduino eSPI Demo

This project is used to test the R61529 addition to the TFT-eSPI library. It uses Clion and Platformio, but it should be easy to convert it to another compiler.
The excelent TFT-eSPI library does not contain support for the R61529 yet, but a Pull Request has been submited. The code can be found at https://github.com/jkvatne/TFT_eSPI
Check out the R61529 branch into the lib/TFT_eSPI folder.

# Board

The software has been tested on a custom board. It has a ESP32-S3-WROOM-1-N16R8 module connected to the
R61529 based lcd panel as shown below. It works from 3.3V. The board has a 3.3V supply that has to be turned on by the CPU using pin 48. The background led can be controlled by pin 12.  It has a USB connection via a CP2102N serial bridge.

# LCD Panel

The LCD panel comes from  [Aliexpress](https://www.aliexpress.com/item/32940608152.html)), and is the version with LCD and Capacitive Touch. It uses the FT6206 touch controller. Note that only 8-bit paralell mode is possible - no SPI. 

# TFT panel connections

The following connections are used.

- TFT_CS=38
- TFT_DC=47
- TFT_RST=37
- TFT_WR=11
- TFT_RD=10
- TFT_D0=1
- TFT_D1=2
- TFT_D2=3
- TFT_D3=4
- TFT_D4=5
- TFT_D5=6
- TFT_D6=7
- TFT_D7=8

Note that everything is defined in the platformio.ini file, and the UserSetup.h file is ignored (by setting the USER_SETUP_LOADED symbol in platformio.ini). In this way there is no need to modify files in the lib/TFT_eSPI folder.

# Functionality

The program will display some text using two different fonts, and draw a small red rectangle where it detects a touch. Both portrait mode and landscape mode can be used by changing the ORIENTATION constant in platformio.ini. 

