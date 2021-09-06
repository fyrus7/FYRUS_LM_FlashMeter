# FYRUS LM
Incident Light Meter &amp; White Balance for Photography


# Highlite :

1. Aperture Priority.
2. Shutter Priority.
3. Flash Mode.
4. ND Filter Mode (v1 only)
5. Temperature (White Balance) Reading.
6. EV Reading.
7. Battery Reading.
8. Battery Voltage Reading

- Aperture: f/1.0 to f/22.0
- Shutter: 1/10000 to 133 sec.
- ISO: 8 - 4 000 000



# What you need :

1. Arduino Nano v3
2. SSD1306 Oled Display (0.96" / 128x64).
3. BH1750 / BH1750FVI Light Sensor.
4. TCS34725 RGB Sensor.
5. 6pcs Tactile Button (3pcs for v2)
6. Lipo 1S 3.7v Battery.
7. (optional) 5V Step-Up Boost Converter (RECOMMENDED TO USE).

* can use ordinary AA/AAA batteries, but power below 3v will show empty battery. A small modification is needed.


# Library Needed :

1. Adafruit SSD1306 Library
2. Adafruit GFX Library
3. BH1750 Library
4. Adafruit TCS34725 Library
5. BatterySense Library


# Revision :

1. Version 1 = 6 button operation
- Metering
- Plus
- Minus
- Priority Switch
- Menu
- Flash Mode

2. Version 2 = 3 button operation
- (Metering / Plus / Minus)
- ISO set : hold Plus + Minus button.
- Priority Switch : hold Metering + Plus button.
- Flash Mode : hold Metering + Minus button.

# ATTENTION!
The Software will store last value metered. Therefor, the second time you press metering button, it actually show the last value stored. Meter twice to get a new value.

# disclaimer

the Software is originally based from a fews old projects i found, combining into one with an upgrading, fixing, optimized and adjustments.
