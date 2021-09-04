# FYRUS LM
Incident Light Meter &amp; White Balance for Photography


# Highlite

1. Aperture Priority.
2. Shutter Priority.
3. Flash Mode.
4. ND Filter Mode.
5. Temperature (White Balance) Reading.
6. EV Reading.
7. Battery Reading.
8. Battery Voltage Reading

- Aperture: f/1.0 to f/22.0
- Shutter: 1/10000 to 133 sec.
- ISO: 8 - 4 000 000



# What you need:

1. Arduino Nano v3
2. SSD1306 Oled Display (0.96" / 128x64).
3. BH1750 / BH1750FVI Light Sensor.
4. TCS34725 RGB Sensor.
5. 6x Tactile Button.
6. Lipo 1S 3.7v Battery.
7. (optional) 5V Step-Up Boost Converter (RECOMMENDED TO USE).

* can use ordinary AA/AAA batteries, power below 3v will show empty battery. A small modification is needed.


# Library needed

1. Adafruit SSD1306 Library
2. Adafruit GFX Library
3. BH1750 Library
4. Adafruit TCS34725 Library
5. BatterySense Library


# to do :
i failed this due to the lack of knowledge, if anyone got the idea please update the code, very much appreciate.

1. use One Tactile button & One EC11 Rotary switch with Push button.
- tactile button = metering.
- rotary switch = press once (aperture/shutter priority), press twice (ISO/ND mode), hold (flash on/off).

OR,

2. use 3 Tactile button (R, Bn1, Bn2)
- R = metering.
- Bn1 & Bn2 = aperture/shutter priority mode.
- R & Bn1 = ISO/ND mode.
- R & Bn2 = switching flash mode on/off.
-
-
-
-
-
- this Software is originally based from a fews old projects i found, combining into one with an upgrading, fixing, optimized and adjustments.
