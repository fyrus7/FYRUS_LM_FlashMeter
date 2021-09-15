# FYRUS LM
Incident Light Meter &amp; White Balance for Photography


# Highlite :

1. Aperture Priority.
2. Shutter Priority.
3. Flash Mode.
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

* can use ordinary AA/AAA batteries, but power below 3v will show empty battery. A small modification is needed.


# Library Needed :

All library are included in Library folder.


# Button Usage :

3 button operation
- (Metering / Plus / Minus)
- ISO set : hold Plus + Minus button.
- Priority Switch : hold Metering + Plus button.
- Flash Mode : hold Metering + Minus button.


# ATTENTION!
The Software will store last value metered. Therefor, the second time you press metering button, it actually show the last value stored. Meter twice to get a new value.

# disclaimer

the Software is originally based from a fews old projects i found, combining into one with an upgrading, fixing, optimized and adjustments.
