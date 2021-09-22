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
6. Battery Reading.
7. Battery Volt and % Reading.

- Aperture: f/1.0 to f/22.
- Shutter: 1/10000 to 133 sec.
- ISO: 8 - 4 000 000.



# What you need :

1. Arduino Nano v3.
2. SSD1306 Oled Display 0.96" 128x64.
3. BH1750 / BH1750FVI Light Sensor.
4. TCS34725 RGB Sensor.
5. 3pcs Tactile Button.
6. Lipo 3.7v Battery.
7. 5V Step-Up Boost Converter (optional for better performance).

* if ordinary AA/AAA batteries is use, power below 3v will show empty battery. A small modification to the code is needed.


# Library Needed :

- All library are included in Library folder.
- Please install all the library needed to your IDE.

# Button Usage :

3 button operation
- (Metering / Plus / Minus)
- ISO set : hold Plus + Minus button.
- Priority Switch : hold Metering + Plus button.
- Flash Mode : hold Metering + Minus button.

- p/s: i have try with encoder (with push button) but it just slow the operation LoL. Therefor i kept it for 3 button operation.


# ATTENTION!
The Software will store last value metered to EEPROM. Therefor, the second time you press metering button, it actually show the last value stored before. Meter twice to get a precise new value.

