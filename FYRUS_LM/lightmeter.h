void outOfrange() {
  display.println(F("--"));
}

void SaveSettings() {
  // Save lightmeter setting into EEPROM.
  EEPROM.write(ndIndexAddr, ndIndex);
  EEPROM.write(ISOIndexAddr, ISOIndex);
  EEPROM.write(modeIndexAddr, modeIndex);
  EEPROM.write(apertureIndexAddr, apertureIndex);
  EEPROM.write(T_expIndexAddr, T_expIndex);
  EEPROM.write(meteringModeAddr, meteringMode);
}

void footer() {
}

/*
  Get light value
*/
float getLux() {
  uint16_t lux = lightMeter.readLightLevel();

  if (lux >= 65534) {
    // light sensor is overloaded.
    Overflow = 1;
    lux = 65535;
  } else {
    Overflow = 0;
  }

  return lux * DomeMultiplier;        // DomeMultiplier = 2.17 (calibration)*/
}                                     // edit 2.17 value in define constant to calibrate

float log2(float x) {
  return log(x) / log(2);
}

float lux2ev(float lux) {
  return log2(lux / 2.5);
}

// return aperture value (1.4, 1.8, 2.0) by index in sequence (0, 1, 2, 3, ...).
float getApertureByIndex(uint8_t indx) {
  float roundIndx = 10.0;

  if (indx > 39) {
    roundIndx = 1;
  }

  float f = round(pow(2, indx / 3.0 * 0.5) * roundIndx) / roundIndx;

// the formula returns exact value, but photographers uses more memorable values.
// convert it.

  if (f >= 1.1 && f < 1.2) {
    f = 1.1;
  } else if (f >= 1.2 && f < 1.4) {
    f = 1.2;
  } else if (f > 3.2 && f < 4) {
    f = 3.5;
  } else if (f > 5 && f < 6.3) {
    f = 5.6;
  } else if (f > 10 && f < 11) {
    f = 10;
  } else if (f >= 11 && f < 12) {
    f = 11;
  } else if (f >= 12 && f < 14) {
    f = 13;
  } else if (f >= 14 && f < 16) {
    f = 14;
  } else if (f >= 20 && f < 22) {
    f = 20;
  } else if (f >= 22 && f < 25) {
    f = 22;
  } else if (f >= 24 && f < 28) {
    f = 25;
  } else if (f >= 28 && f < 40) {
    f = 36;
  } else if (f >= 40 && f < 45) {
    f = 40;
  } else if (f >= 45 && f < 50) {
    f = 45;
  } else if (f >= 50 && f < 57) {
    f = 51;
  } else if (f >= 71 && f < 80) {
    f = 72;
  } else if (f >= 80 && f < 90) {
    f = 80;
  } else if (f >= 90 && f < 101) {
    f = 90;
  }

  return f;
}

// Return ISO value (100, 200, 400, ...) by index in sequence (0, 1, 2, 3, ...).
long getISOByIndex(uint8_t indx) {
  if (indx < 0 || indx > MaxISOIndex) {
    indx = 0;
  }

  indx += 10;

//  float iso = pow(10, (indx - 1) / 10.0);
//  iso = (long)(round(iso / 10.0) * 10);

  long int factor = 1;
  float iso = 0;

  if (indx > 60) {
    indx -= 50;
    factor = 100000;
  } else if (indx > 50) {
    indx -= 40;
    factor = 10000;
  } else if (indx > 40) {
    indx -= 30;
    factor = 1000;
  } else if (indx > 30) {
    indx -= 20;
    factor = 100;
  } else if (indx > 20) {
    indx -= 10;
    factor = 10;
  }

  if (indx == 10) {
    iso = 8;
  } else if (indx == 11) {
    iso = 10;
  } else if (indx == 12) {
    iso = 12.5;
  } else if (indx == 13) {
    iso = 16;
  } else if (indx == 14) {
    iso = 20;
  } else if (indx == 15) {
    iso = 25;
  } else if (indx == 16) {
    iso = 32;
  } else if (indx == 17) {
    iso = 40;
  } else if (indx == 18) {
    iso = 50;
  } else if (indx == 19) {
    iso = 64;
  } else if (indx == 20) {
    iso = 80;
  }

  iso = (long)floor(iso * factor);
  return iso;
}

float getMinDistance(float x, float v1, float v2) {
  if (x - v1 > v2 - x) {
    return v2;
  }

  return v1;
}

float getTimeByIndex(uint8_t indx) {
  if (indx < 0 || indx >= MaxTimeIndex) {
    indx = 0;
  }

  float factor = 0;
  float t = 0;

  if (indx < 10) {
    factor = 100.0;
  } else if (indx < 20) {
    indx -= 10;
    factor = 10.0;
  } else if (indx < 30) {
    indx -= 20;
    factor = 1.0;
  } else if (indx < 40) {
    indx -= 30;
    factor = 0.1;
  } else if (indx < 50) {
    indx -= 40;
    factor = 0.01;
  } else if (indx < 60) {
    indx -= 50;
    factor = 0.001;
  } else if (indx < 70) {
    indx -= 60;
    factor = 0.0001;
  } else if (indx < 80) {
    indx -= 70;
    factor = 0.00001;
  }

  if (indx == 0) {
    t = 100;
  } else if (indx == 1) {
    t = 80;
  } else if (indx == 2) {
    t = 64;
  } else if (indx == 3) {
    t = 50;
  } else if (indx == 4) {
    t = 40;
  } else if (indx == 5) {
    t = 32;
  } else if (indx == 6) {
    t = 25;
  } else if (indx == 7) {
    t = 20;
  } else if (indx == 8) {
    t = 16;
  } else if (indx == 9) {
    t = 12.5;
  }

  t = 1 / (t * factor);
  return t;
}

// Convert calculated time (in seconds) to photograpy style shutter speed. 
double fixTime(double t) {
  double divider = 1;

  float maxTime = getTimeByIndex(MaxTimeIndex);

  if (t < maxTime) {
    return maxTime;
  }

  t = 1 / t;

  if (t > 99999) {
    divider = 10000;
  } else if (t > 9999) {
    divider = 1000;
  } else if (t > 999) {
    divider = 100;
  } else if (t > 99) {
    divider = 10;
  }

  t = t / divider;

  if (t >= 10 && t <= 12.5) {
    t = getMinDistance(t, 10, 12.5);
  } else if (t >= 12.5 && t <= 16) {
    t = getMinDistance(t, 12.5, 16);
  } else if (t >= 16 && t <= 20) {
    t = getMinDistance(t, 16, 20);
  } else if (t >= 20 && t <= 25) {
    t = getMinDistance(t, 20, 25);
  } else if (t >= 25 && t <= 32) {
    t = getMinDistance(t, 25, 32);
  } else if (t >= 32 && t <= 40) {
    t = getMinDistance(t, 32, 40);
  } else if (t >= 40 && t <= 50) {
    t = getMinDistance(t, 40, 50);
  } else if (t >= 50 && t <= 64) {
    t = getMinDistance(t, 50, 64);
  } else if (t >= 64 && t <= 80) {
    t = getMinDistance(t, 64, 80);
  } else if (t >= 80 && t <= 100) {
    t = getMinDistance(t, 80, 100);
  }

  t = t * divider;

  if (t == 32) {
    t = 30;
  }

  if (t == 16) {
    t = 15;
  }

  t = 1 / t;

  return t;
}

// Convert calculated aperture value to photograpy style aperture value. 
float fixAperture(float a) {
  for (int i = 0; i < MaxApertureIndex; i++) {
    float a1 = getApertureByIndex(i);
    float a2 = getApertureByIndex(i + 1);

    if (a1 < a && a2 >= a) {
      return getMinDistance(a, a1, a2);
    }
  }

  return 0;
}

/*
  Return ND from ndIndex
  int ND[] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48}; // eg.: 1) 0.3 ND = -1 stop = 2^2 = 4; 2) 0.9 ND = -3 stop = 2^3 = 16;
*/
uint8_t getND(uint8_t ndIndex) {
  if (ndIndex == 0) {
    return 0;
  }

  return 3 + (ndIndex - 1) * 3;
}

// Calculate new exposure value and display it.
void refresh() {
  ISOMenu = false;
  mainScreen = true;
  NDMenu = false;

  float EV = lux2ev(lux);

  float T = getTimeByIndex(T_expIndex);
  float A = getApertureByIndex(apertureIndex);
  long  iso = getISOByIndex(ISOIndex);

  uint8_t ndStop = getND(ndIndex);

  // if ND filter is configured then make corrections.
  // As ISO is a main operand in all EV calculations we can adjust ISO by ND filter factor.
  // if ND4 (ND 0.6) filter is configured then we need to adjust ISO to -2 full stops. Ex. 800 to 200
  if (ndIndex > 0) {
    ISOND = iso / (pow(2, ndIndex));
  } else {
    ISOND = iso;
  }

  if (lux > 0) {
    if (modeIndex == 0) {
      // Aperture priority. Calculating time.
      T = fixTime(100 * pow(A, 2) / ISOND / pow(2, EV)); //T = exposure time, in seconds

      // Calculating shutter speed index for correct menu navigation.
      for (int i = 0; i <= MaxTimeIndex; i++) {
        if (T == getTimeByIndex(i)) {
          T_expIndex = i;
          break;
        }
      }
    } else if (modeIndex == 1) {
      // Shutter speed priority. Calculating aperture.
      A = fixAperture(sqrt(pow(2, EV) * ISOND * T / 100));

      // Calculating aperture index for correct menu navigation.
      if (A > 0) {
        for (int i = 0; i <= MaxApertureIndex; i++) {
          if (A == getApertureByIndex(i)) {
            apertureIndex = i;
            break;
          }
        }
      }
    }
  } else {
    if (modeIndex == 0) {
      T = 0;
    } else {
      A = 0;
    }
  }

  uint8_t Tdisplay = 0; // Flag for shutter speed display style (fractional, seconds, minutes)
  double  Tfr = 0;
  float   Tmin = 0;

  if (T >= 60) {
    Tdisplay = 0;  // Exposure is in minutes
    Tmin = T / 60;

  } else if (T < 60 && T >= 0.5) {
    Tdisplay = 2;  // Exposure in in seconds

  } else if (T < 0.5) {
    Tdisplay = 1;  // Exposure is in fractional form
    Tfr = round(1 / T);
  }

/* /////// UI DISPLAY STARTS HERE /////// */

  uint8_t linePos[] = {17, 37};
  display.clearDisplay();
  display.setTextColor(WHITE);


/* APERTURE DISPLAY /////// */
  display.setTextSize(1);
  display.setCursor(0, 1);
  display.print(F("f/"));
  display.setCursor(13, 1);
  display.setTextSize(3);
  if (A > 0) {
    if (A >= 100) {
      display.print(A, 0);
    } else {
      display.print(A, 1);
    }
  } else {
    outOfrange();
  }


/* SHUTTER DISPLAY /////// */
    display.setTextSize(2);
    display.setCursor(0, 38);
  if (Tdisplay == 0) {
    display.print(Tmin, 1);
    display.print(F("m"));
  } else if (Tdisplay == 1) {
    if (T > 0) {
      display.print(F("1/"));
      display.print(Tfr, 0);
    } else {
      outOfrange();
    }
  } else if (Tdisplay == 2) {
    display.print(T, 1);
    display.print(F("s"));
  } else if (Tdisplay == 3) {
    outOfrange();
  }


/* SETUP TEXT SIZE & COLOR /////// */
  display.setTextColor(WHITE); // SET COLOR WHITE
  display.setTextSize(1); // TEXT IN SIZE 1


/* PRIORITY MARKING (Aperture/Shutter) /////// */
  if (modeIndex == 0) {
    // Aperture mode
    display.setTextColor(WHITE);
    display.setCursor(36, 26);
    display.print(F("APERTURE"));
    display.drawLine(0, 26, 26, 26, WHITE);
    display.drawLine(26, 26, 32, 32, WHITE);
    
  } else if (modeIndex == 1) { 
    // Shutter mode
    display.setCursor(0, 26);
    display.print(F("SHUTTER"));
    display.drawLine(50, 32, 82, 32, WHITE);
    display.drawLine(44, 26, 50, 32, WHITE);

  }


/* BATTERY PERCENTAGE /////// */
    display.setCursor(104, 39);
     if (perc = 4.2) {
       display.drawBitmap(89, 39, battery_full, 16, 8, WHITE);
        display.print(F("100"));
    } else if (perc = 4.0) {
       display.drawBitmap(89, 39, battery_threequarters, 16, 8, WHITE);
        display.print(F("80"));
    } else if (perc = 3.9) {
       display.drawBitmap(89, 39, battery_half, 16, 8, WHITE);
        display.print(F("60"));
    } else if (perc = 3.7) {
       display.drawBitmap(89, 39, battery_low, 16, 8, WHITE);
        display.print(F("20"));
    } else if (perc = 3.6) {
       display.drawBitmap(89, 39, battery_empty, 16, 8, WHITE);
        display.print(F("00"));
    }
       display.println(F("%"));
    

/* METERING MODE DISPLAY (SWITCHING AMBIENT/FLASH) /////// */
  if (meteringMode == 0) {
/* (F("AMBIENT")); */ 
  } else if (meteringMode == 1) {
    display.setCursor(88, 54);
    display.print(F(" FLASH "));
    display.drawRect(90, 51, 38, 13, WHITE);
  }


/* WHITE BALANCE DISPLAY (in Kelvin - TCS34725) /////// */
   display.drawRect(86, 1, 42, 23, WHITE);
   display.setCursor(96, 4);
   display.print(F("TEMP"));

  if (rgb_sensor.ct > 9999) {
    display.setCursor(99, 14);
    display.print(rgb_sensor.ct / 1000.0, 0);
 } else {
    display.setCursor(93, 14);
    display.print(rgb_sensor.ct);
  } display.print(F("K"));


/*  LINE DIVISOR  /////// */
   display.drawLine(86, 27, 86, 64, WHITE);
/*
// LUX PRINT
  display.setCursor(92, 1);
  display.print(F("LUX"));
  display.print(lux, 0);
*/


/* EV DISPLAY /////// */
  display.setCursor(90, 28);
  display.print(F("EV:"));
  if (lux > 0) {
    display.println(EV, 0);
  } else {
    display.println(0, 0);
  }


/* ISO DISPLAY /////// */
  display.setCursor(0, 57);
  display.print(F("ISO:"));

  if (iso > 999999) {
    display.print(iso / 1000000.0, 2);
    display.print(F("M"));
  } else if (iso > 9999) {
    display.print(iso / 1000.0, 0);
    display.print(F("K"));
  } else {
    display.print(iso);
  }


/* ND FILTER INDICATOR // ND FILTER PRINT (available only after turn ON) /////// */
  if (ndIndex > 0) {
    display.setCursor(48, 57);
    display.print(F("+ND"));
    display.print(pow(2, ndIndex), 0);
/*    display.setCursor(104, 57);
    display.print(F("="));
    display.println(ndStop / 10.0, 1); */
  }

  display.display();
}


void showISOMenu() {
  ISOMenu = true;
  NDMenu = false;
  mainScreen = false;

/* ISO MENU /////// */
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(48, 1);
  display.println(F("ISO"));
  display.setTextSize(1);
  display.setCursor(45, 17);
  display.println(F("SETTING"));
  display.setTextSize(3);

  long iso = getISOByIndex(ISOIndex);

  if (iso > 999999) {
    display.setCursor(0, 35);
  } else if (iso > 99999) {
    display.setCursor(10, 35);
  } else if (iso > 9999) {
    display.setCursor(20, 35);
  } else if (iso > 999) {
    display.setCursor(30, 35);
  } else if (iso > 99) {
    display.setCursor(40, 35);
  } else {
    display.setCursor(50, 35);
  }

  display.print(iso);

  display.display();
  delay(200);
}


/* ND MENU /////// */
void showNDMenu() {
  ISOMenu = false;
  mainScreen = false;
  NDMenu = true;

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(49, 1);
  display.println(F("N.D"));
  display.setTextSize(1);
  display.setCursor(45, 17);
  display.println(F("SETTING"));
  
  display.setTextSize(3);
  if (ndIndex > 9) {
    display.setCursor(10, 35);
  } else if (ndIndex > 6) {
    display.setCursor(20, 35);
  } else if (ndIndex > 3) {
    display.setCursor(30, 35);
  } else {
    display.setCursor(40, 35);
  }

  if (ndIndex > 0) {
    display.print(F("ND"));
    display.print(pow(2, ndIndex), 0);
  } else {
    display.setTextSize(2);
    display.setCursor(12, 40);
    display.print(F("No Filter"));
  }

  display.display();
  delay(200);
}


/* NAVIGATION MENU /////// */
void menu() {
  if (MenuButtonState == 0) {
    if (mainScreen) {
      showISOMenu();
    } else if (ISOMenu) {
      showNDMenu();
    } else {
      refresh();
      delay(200);
    }
  }

  if (NDMenu) {
    if (PlusButtonState == 0) {
      ndIndex++;

      if (ndIndex > MaxNDIndex) {
        ndIndex = 0;
      }
    } else if (MinusButtonState == 0) {
      if (ndIndex <= 0) {
        ndIndex = MaxNDIndex;
      } else {
        ndIndex--;
      }
    }

    if (PlusButtonState == 0 || MinusButtonState == 0) {
      showNDMenu();
    }
  }

  if (ISOMenu) {
    // ISO change mode
    if (PlusButtonState == 0) {
      // increase ISO
      ISOIndex++;

      if (ISOIndex > MaxISOIndex) {
        ISOIndex = 0;
      }
    } else if (MinusButtonState == 0) {
      if (ISOIndex > 0) {
        ISOIndex--;
      } else {
        ISOIndex = MaxISOIndex;
      }
    }

    if (PlusButtonState == 0 || MinusButtonState == 0) {
      showISOMenu();
    }
  }

  if (ModeButtonState == 0) {
    // switching between Aperture priority and Shutter Speed priority.
    if (mainScreen) {
      modeIndex++;
      if (modeIndex > 1) {
        modeIndex = 0;
      }
    }

    refresh();
    delay(200);
  }

  if (mainScreen && MeteringModeButtonState == 0) {
    // Switch between Ambient light and Flash light metering
    if (meteringMode == 0) {
      meteringMode = 1;
    } else {
      meteringMode = 0;
    }

    refresh();
    delay(200);
  }

  if (mainScreen && (PlusButtonState == 0 || MinusButtonState == 0)) {
    if (modeIndex == 0) {
      // Aperture priority mode
      if (PlusButtonState == 0) {
        // Increase aperture.
        apertureIndex++;

        if (apertureIndex > MaxApertureIndex) {
          apertureIndex = 0;
        }
      } else if (MinusButtonState == 0) {
        // Decrease aperture
        if (apertureIndex > 0) {
          apertureIndex--;
        } else {
          apertureIndex = MaxApertureIndex;
        }
      }
    } else if (modeIndex == 1) {
      // Time priority mode
      if (PlusButtonState == 0) {
        // increase time
        T_expIndex--;

        if (T_expIndex > MaxTimeIndex) {
          T_expIndex = 0;
        }
      } else if (MinusButtonState == 0) {
        // decrease time
        if (T_expIndex > 0) {
          T_expIndex++;
        } else {
          T_expIndex = MaxTimeIndex;
        }
      }
    }

    delay(200);

    refresh();
  }
}

/*
  Read buttons state
*/
void readButtons() {
  PlusButtonState = digitalRead(PlusButtonPin);
  MinusButtonState = digitalRead(MinusButtonPin);
  MeteringButtonState = digitalRead(MeteringButtonPin);
  ModeButtonState = digitalRead(ModeButtonPin);
  MenuButtonState = digitalRead(MenuButtonPin);
  MeteringModeButtonState = digitalRead(MeteringModeButtonPin);
}
