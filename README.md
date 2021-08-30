# FYRUS LM / Arduino Photography Light Meter
Incident Light Meter &amp; White Balance for Photography


# Highlite

1. Aperture Priority.
2. Shutter Priority.
3. Flash Mode.
4. ND Filter Mode.
5. Temperature Reading (White Balance).
6. EV Reading.
7. Battery Reading

- Aperture: f/1.0 to f/22.0
- Shutter: 1/10000 to 133 sec.
- ISO: 8 - 4 000 000



# What you need:

1. Arduino Nano v3

2. 128x64 (0.96) Oled Display.
- 4 pin or 7 pin (SPI) display both can use.
- i have write the code for 7 pin. Just follow instructions in the note.


3. BH1750 / BH1750FVI Light Sensor.
- (GY-30 & GY-302 are same, just different in their size)

4. TCS34725 RGB Sensor.

5. 6x Tactile Button.

6. Lipo 1S 3.7v Battery.

7. (optional) Electronic enclosure case.

-

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


this Software is originally based from a fews projects, combining into one with a fix, optimizations and adjustment.
