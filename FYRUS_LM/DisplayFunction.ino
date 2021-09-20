/*
 * 
 * Fyrus LM v2.1
 * Photography Light Meter & White Balance.
 * 
 */

 
 /* /////// DISPLAY /////// */


  display.clearDisplay();
  display.setTextColor(WHITE);


// Shutter priority mode
if (modeIndex == 1) {

// APERTURE
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print(F("f/"));
  display.setCursor(14, 5);
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
    
// SHUTTER
    display.setTextSize(2);
    display.setCursor(0, 37);
    //display.print(F("T:"));
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


// Aperture priority mode
} else if (modeIndex == 0) {

// SHUTTER
    display.setTextSize(2);
    display.setCursor(0, 9);
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
  
// APERTURE
  display.setTextSize(1);
  display.setCursor(0, 37);
  display.print(F("f/"));
  display.setTextSize(2);
  if (A > 0) {
    if (A >= 100) {
      display.print(A, 0);
    } else {
      display.print(A, 1);
    }
  } else {
    outOfrange();
  }
}


/* DEFINE SAME TEXT SIZE & COLOR BELOW THIS RANGE  */
  display.setTextColor(WHITE);
  display.setTextSize(1);


// METERING MODE (AMBIENT/FLASH)
  if (meteringMode == 0) {
  } else if (meteringMode == 1) {
    
    display.drawBitmap(94, 55, _rect, 33, 12, WHITE);
    display.setCursor(96, 56);
    display.setTextColor(BLACK);
    display.print(F("FLASH"));
  }


   display.setTextColor(WHITE);


// WHITE BALANCE METERING
   display.drawRect(90, 1, 38, 34, WHITE);;
   display.setCursor(98, 8);
   display.print(F("TEMP"));

  if (rgb_sensor.ct > 9999) {
    display.setCursor(101, 20);
    display.print(rgb_sensor.ct / 1000.0, 0);
 } else {
    display.setCursor(98, 20);
    display.print(rgb_sensor.ct / 1000.0, 1);
 }  display.print(F("K"));

   
// BATTERY PERCENTAGE
 if (battery.level() > 80 && battery.level() < 100) {
    display.drawBitmap(89, 42, _full, 16, 8, WHITE);
 } else if (battery.level() > 60 && battery.level() < 80) {
    display.drawBitmap(89, 42, _threequarters, 16, 8, WHITE);
 } else if (battery.level() > 40 && battery.level() < 60) {
    display.drawBitmap(89, 42, _half, 16, 8, WHITE);
 } else if (battery.level() > 30 && battery.level() < 40) {
    display.drawBitmap(89, 42, _low, 16, 8, WHITE);
 } else {
    display.drawBitmap(89, 42, _empty, 16, 8, WHITE);
 }

  display.setCursor(104, 43);
  display.print(battery.level());
  display.println(F("%"));


// EV
  display.setCursor(51, 57);
  display.print(F(" EV:"));
  if (lux > 0) {
    display.println(EV, 0);
  } else {
    display.println(0, 0);
  }


// ISO
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

  display.display();
}


void showISOset() {
  ISOset = true;
  Screen = false;

// ISO SETUP
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 5);
  display.println(F("ISO SPEED"));
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


/* /////// FUNCTION /////// */

  void menu() {
  if (!Bn1 && !Bn2) {
    if (Screen) {
      showISOset();
    } else {
      refresh();
      delay(200);
    }
  }

  if (ISOset) {  
    // ISO change mode
    if (!Bn1) {
      // increase ISO
      ISOIndex++;

      if (ISOIndex > MaxISOIndex) {
        ISOIndex = 0;
      }
    } else if (!Bn2) {
      if (ISOIndex > 0) {
        ISOIndex--;
      } else {
        ISOIndex = MaxISOIndex;
      }
    }
    if (!Bn1 || !Bn2) {
      showISOset();
    }
  }

// Switch between Ambient light and Flash light metering
  if (Screen && !R && !Bn2) {
    if (meteringMode == 0) {
      meteringMode = 1;
      
display.clearDisplay();
display.display();
delay(2000);

    } else {
      meteringMode = 0;

display.clearDisplay();
display.display();
delay(500);

    }

    refresh();
    delay(200);
  }

// switching between Aperture priority and Shutter Speed priority.
  if (!R && !Bn1) {
    if (Screen) {
      modeIndex++;

display.clearDisplay();
display.display();
delay(100);

      if (modeIndex > 1) {
        modeIndex = 0;
      }
    }

    refresh();
    delay(200);
  }
  
  if (Screen && (!Bn1 || !Bn2)) {
    if (modeIndex == 0) {
      // Aperture priority mode
      if (!Bn1) {
        // Increase aperture.
        apertureIndex++;

        if (apertureIndex > MaxApertureIndex) {
          apertureIndex = 0;
        }
      } else if (!Bn2) {
        // Decrease aperture
        if (apertureIndex > 0) {
          apertureIndex--;
        } else {
          apertureIndex = MaxApertureIndex;
        }
      }
    } else if (modeIndex == 1) {
      // Time priority mode
      if (!Bn1) {
        // increase time
        T_expIndex--;

        if (T_expIndex > MaxTimeIndex) {
          T_expIndex = 0;
        }
      } else if (!Bn2) {
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

void Read() {
  
    Bn1 = digitalRead(Bn1p);
    Bn2 = digitalRead(Bn2p);
    R   = digitalRead(Rp);

}
