# FYRUS LM
Incident Flash Meter, Light Meter & White Balance for Photography

- Current version : 2.3
- Date : 23 / 09 / 2021


# Functions :

1. Flash Metering.
2. Aperture Priority.
3. Shutter Priority.
4. Temperature (White Balance) Reading.
5. EV Reading.
6. Battery Volt & Percentage.

- Aperture : f/1.0 to f/22.
- Shutter : 1/10000 to 50sec.
- ISO : 8 - 4 000 000.



# What you need :

1. Arduino Nano v3.
2. SSD1306 Oled Display 0.96" 128x64.
3. BH1750 / BH1750FVI Light Sensor.
4. TCS34725 RGB Sensor.
5. 3pcs Tactile Button.
6. Lipo 3.7v Battery.
7. 5V Step-Up Boost Converter (optional for better performance).

* if ordinary AA/AAA batteries is use, power below 3v will show empty battery. A small modification to the code is needed.
I
* Board voltage is based on 5v, your board voltage maybe less than that. Change the value based on your board output (use multimeter) for better accuracy.

# Library Needed :

- All library are included in Library folder.
- Please install all the library needed to your IDE.

# Button Operation :

- 3 button for Metering | Plus | Minus
-
- ISO setup : hold Plus + Minus button.
- Priority Mode : hold Metering + Plus button.
- Flash On/Off : hold Metering + Minus button.




# ATTENTION!
The Software will store last value metered to EEPROM. Therefor, the second time you press metering button, it actually show the last value stored before. Meter twice to get a precise new value.

