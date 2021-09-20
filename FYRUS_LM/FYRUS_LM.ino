/* ---------------------------------------------------------- *
 *  
 * Fyrus LM v2.1
 * Photography Light Meter & White Balance.
 * 
 * 3 Button Operation:
 * > button 1 = Metering
 * > button 2 = Plus
 * > button 3 = Minus
 * 
 * Component:
 * 1. Arduino Nano v3.
 * 2. Oled I2C Display ( 0.96" SSD1306 128x64 ).
 * 3. BH1750 / BH1750FVI Light Sensor.
 * 4. TCS34725 RGB Sensor.
 * 5. Tactile Button.
 * 6. LiPo 3.7v Battery.
 * 7. 5V Step-Up Boost Converter.
 * 
 * note:
 * Power below 3.0v will show battery empty,
 *
 * ---------------------------------------------------------- *
 * 
 * Wiring:
 * 
 * > Button
 *   pin 2
 *   pin 3
 *   pin 4
 *   GND to GND
 *
 * > Display & Sensors
 *   VCC -> 3.3V
 *   GND -> GND
 *   SDA -> pin A4
 *   SCL -> pin A5
 *
 * > Battery
 * 
 *                                           +------+
 *          +---------------------------- A0 |      |
 *          |       +-------+                |      |
 *   BAT+ --+-- IN+ | 5V    | OUT+ -----  5V | Nano |
 *                  | BOOST |                |   v3 |
 *   BAT- ----- IN- |       | OUT- ----- GND |      |
 *                  +-------+                +------+
 *
 * ---------------------------------------------------------- *
 */

static const unsigned char PROGMEM FLM [] = {
0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF,
0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x06, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFE, 0x0E, 0x00, 0x00, 0x70, 0x03,
0xFE, 0x00, 0x00, 0x03, 0xFE, 0x0E, 0x00, 0x00, 0x70, 0x03, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x0C,
0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xDE, 0xFF, 0xFF, 0x7B, 0xF8, 0x00, 0xFC,
0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x1F, 0xF0, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x03, 0x1F, 0xF0,
0x00, 0x01, 0xFF, 0xFB, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF9, 0xE0, 0x00,
0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF9, 0xF0, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFE, 0x13,
0xFF, 0xF9, 0xF8, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x3C, 0xFF, 0xFD, 0xFE, 0x00, 0x00, 0x03,
0x80, 0x00, 0x00, 0x7E, 0x3F, 0xFD, 0xFF, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xFF, 0x9F, 0xFD,
0xFF, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xFF, 0xC7, 0xFD, 0xFF, 0x80, 0x00, 0x03, 0x80, 0x00,
0x03, 0xFF, 0xF3, 0xFD, 0xFF, 0xC0, 0x00, 0x03, 0x80, 0x00, 0x03, 0xFF, 0xF8, 0xFC, 0xFF, 0xC0,
0x00, 0x03, 0x80, 0x00, 0x07, 0xFF, 0xFE, 0x7C, 0xFF, 0xE0, 0x00, 0x03, 0x80, 0x00, 0x07, 0xFF,
0xFE, 0x1C, 0xFF, 0xC0, 0x00, 0x03, 0x80, 0x00, 0x0F, 0xFF, 0xE0, 0x0C, 0xFF, 0x90, 0x00, 0x03,
0x80, 0x00, 0x0F, 0xFF, 0x00, 0x06, 0xFF, 0x30, 0x00, 0x03, 0x80, 0x00, 0x0F, 0xF8, 0x00, 0x00,
0xFE, 0x70, 0x00, 0x03, 0x80, 0x00, 0x0F, 0xC3, 0x80, 0x00, 0xFC, 0xF0, 0x00, 0x03, 0x80, 0x00,
0x1E, 0x1F, 0x00, 0x00, 0xF9, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x10, 0xFF, 0x00, 0x00, 0xF3, 0xF8,
0x00, 0x03, 0x80, 0x00, 0x03, 0xFF, 0x00, 0x00, 0xE7, 0xF8, 0x00, 0x03, 0x80, 0x00, 0x1F, 0xFE,
0x00, 0x00, 0xCF, 0xF8, 0x00, 0x03, 0x80, 0x00, 0x1F, 0xFE, 0x00, 0x00, 0x9F, 0xF8, 0x00, 0x03,
0x80, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x03, 0x80, 0x00, 0x1F, 0xFD, 0x00, 0x00,
0x7F, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x1F, 0xFD, 0x80, 0x00, 0xFF, 0xF0, 0x00, 0x03, 0x80, 0x00,
0x0F, 0xF9, 0x80, 0x01, 0xFF, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x0F, 0xFB, 0xC0, 0x03, 0xFF, 0xF0,
0x00, 0x03, 0x80, 0x00, 0x0F, 0xF3, 0xC0, 0x0F, 0xFF, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x07, 0xF3,
0xE0, 0x03, 0xFF, 0xE0, 0x00, 0x03, 0x80, 0x00, 0x07, 0xF7, 0xF7, 0xE0, 0x01, 0xE0, 0x00, 0x03,
0x80, 0x00, 0x07, 0xE7, 0xF3, 0xFF, 0xE0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x03, 0xE7, 0xFB, 0xFF,
0xFF, 0xC0, 0x5C, 0x03, 0x80, 0x00, 0x01, 0xEF, 0xF9, 0xFF, 0xFF, 0x80, 0x3E, 0x03, 0x80, 0x00,
0x01, 0xCF, 0xFC, 0xFF, 0xFF, 0x80, 0x3E, 0x03, 0x80, 0x00, 0x00, 0xCF, 0xFE, 0xFF, 0xFF, 0x00,
0x3C, 0x03, 0x80, 0x00, 0x00, 0x5F, 0xFE, 0x7F, 0xFE, 0x00, 0x18, 0x03, 0x80, 0x00, 0x00, 0x1F,
0xFF, 0x3F, 0xFC, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x1F, 0xFF, 0x3F, 0xF8, 0x00, 0x00, 0x03,
0x80, 0x00, 0x00, 0x07, 0xFF, 0x9F, 0xE0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x01, 0xFF, 0xCF,
0x80, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x7F, 0xCE, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00,
0x00, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x03, 0x80, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x3E, 0xCC, 0xF9,
0x99, 0xF0, 0x20, 0xE7, 0x80, 0x00, 0x00, 0x30, 0x58, 0x89, 0x9B, 0x10, 0x20, 0xE7, 0xFF, 0xFF,
0xFE, 0x30, 0x70, 0x99, 0x9B, 0x00, 0x20, 0xEF, 0xFF, 0xFF, 0xFE, 0x3C, 0x30, 0xF1, 0x99, 0xF0,
0x20, 0xBB, 0x00, 0x00, 0x00, 0x30, 0x30, 0xB1, 0x98, 0x10, 0x20, 0x9B, 0x00, 0x00, 0x00, 0x30,
0x30, 0x99, 0x9B, 0x30, 0x30, 0xDB, 0x00, 0x00, 0x00, 0x30, 0x30, 0x98, 0xF1, 0xE0, 0x3C, 0xD3 };

static const unsigned char PROGMEM _full [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x5F, 0xB8, 0x5F, 0xB8, 0x5F, 0xB8, 0x5F, 0xB8, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM _threequarters [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x5C, 0x38, 0x5E, 0x38, 0x5E, 0x38, 0x5F, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM _half [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x58, 0x38, 0x58, 0x38, 0x5C, 0x38, 0x5C, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM _low [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x50, 0x38, 0x50, 0x38, 0x50, 0x38, 0x50, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM _empty [] =
{ 0x7F, 0xE0, 0x40, 0x20, 0x40, 0x38, 0x40, 0x38, 0x40, 0x38, 0x40, 0x38, 0x40, 0x20, 0x7F, 0xE0 };

static const unsigned char PROGMEM _rect [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xE1, };


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>
#include <Adafruit_TCS34725.h>
#include <EEPROM.h>
#include <Battery.h>

// DISPLAY
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

BH1750 lightMeter;

// BUTTONS
uint8_t Rp   = 2;                         // Metering button pin
uint8_t Bn1p = 3;                         // + increment button pin
uint8_t Bn2p = 4;                         // - increment button pin


// CONSTANTS & CALIBRATION
#define DomeMultiplier          2.17      // define 1.0 without white translucide Dome on the sensor.
#define TCS34725_R_Coef         0.136
#define TCS34725_G_Coef         1.000
#define TCS34725_B_Coef         -0.444
#define TCS34725_GA             1.0
#define TCS34725_DF             310.0
#define TCS34725_CT_Coef        3810.0
#define TCS34725_CT_Offset      1391.0


// FLOAT & BOOLEAN
boolean Bn1;                              // + increment button state
boolean Bn2;                              // - increment button state
boolean R;                                // Metering button state
float   lux;                              // Lux value from BH1750
float   ct;                               // Color Temp value from TCS34725
boolean Overflow = 0;                     // Sensor got Saturated and Display "Overflow"
float   ISOND;
boolean Screen = false;
boolean ISOset = false;


// INDEX FOR EEPROM MEMORY RECORDING
#define MaxISOIndex             57
#define MaxApertureIndex        27        // max 70 (default f1.0 ~ f22) editable.
#define MaxTimeIndex            80
#define MaxFlashMeteringTime    3000      // flash metering in millisecond (default 3 seconds)

#define ISOIndexAddr            1
#define apertureIndexAddr       2
#define modeIndexAddr           3
#define T_expIndexAddr          4
#define meteringModeAddr        5

#define defaultApertureIndex    12
#define defaultISOIndex         11
#define defaultModeIndex        0
#define defaultT_expIndex       19

uint8_t ISOIndex =          EEPROM.read(ISOIndexAddr);
uint8_t apertureIndex =     EEPROM.read(apertureIndexAddr);
uint8_t T_expIndex =        EEPROM.read(T_expIndexAddr);
uint8_t modeIndex =         EEPROM.read(modeIndexAddr);
uint8_t meteringMode =      EEPROM.read(meteringModeAddr);


// NOTE: Max voltage 4000 is based on average most battery max voltage,
//       some battery max value goes up to 4200.
//       Check your max voltage value with a Multimeter.

// Battery Meter : MinVoltage / MaxVoltage / BattPin       
Battery battery(3000, 4000, A0);


// TCS 34725
class ColorSensor {
  
    public:
  
    void getColorTemp();
    uint16_t r, g, b, c, ir;
    uint16_t ct, lux, r_comp, g_comp, b_comp;
    float cpl;
} rgb_sensor;

void ColorSensor::getColorTemp() {

    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);
  
    tcs.getRawData(&r, &g, &b, &c);
    //lux = tcs.calculateLux(r, g, b);
    // DN40 calculations
    ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
    r_comp = r - ir;
    g_comp = g - ir;
    b_comp = b - ir;
    //c_comp = c - ir;
  
    cpl = (700) / (TCS34725_GA * TCS34725_DF);
    lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
    ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;
    //ct = ct*DomeSum;
}


void setup() {  
 
  pinMode(Bn1p, INPUT_PULLUP);
  pinMode(Bn2p, INPUT_PULLUP);
  pinMode(Rp, INPUT_PULLUP);

  battery.begin(5000, 1.0);

  Wire.begin();
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE_2);
  //lightMeter.begin(BH1750::ONE_TIME_LOW_RES_MODE); // for low resolution but 16ms light measurement time.


  // DISPLAY STARTS
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 

  display.clearDisplay();
  
  display.drawBitmap(24, 0, FLM, 80, 64, 1);
  display.display();
  display.clearDisplay();
  delay(3000);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(18, 1);
  display.println("FYRUS LM");
  
  display.setTextSize(1);

  display.drawLine(8, 51, 120, 51, WHITE);

  if (battery.level() > 30 && battery.level() < 100) {
  display.setCursor(29, 25);
   display.println(F("Batt Voltage"));
  display.setCursor(46, 37);
   display.print(battery.voltage());
    display.print(F("mV"));
  display.setCursor(26, 57);
   display.println("<<< READY >>>");
  } else {
    display.setCursor(29, 32);
     display.print(F("Low Battery!"));
    display.setCursor(31 ,57);
     display.println("NEED CHARGE");
  }

  display.display();
//  delay(2000);


  // IF NO MEMORY WAS RECORDED BEFORE, START WITH THIS VALUES otherwise it will read "255"
  if (apertureIndex > MaxApertureIndex) {
    apertureIndex = defaultApertureIndex;
  }

  if (ISOIndex > MaxISOIndex) {
    ISOIndex = defaultISOIndex;
  }

  if (T_expIndex > MaxTimeIndex) {
    T_expIndex = defaultT_expIndex;
  }

  if (modeIndex < 0 || modeIndex > 1) {
    // Aperture priority. Calculating shutter speed.
    modeIndex = 0;
  }

  if (meteringMode > 1) {
    meteringMode = 0;
  }

  lux = getLux();                      // get Lux reading from BH1750
  rgb_sensor.getColorTemp();           // get White Balance Value from TCS34725
}


void loop() {

    Read();
    menu();

  // Save setting if Metering button is pressed.
  if (!R) {
  
    SaveSettings();

    lux = 0;
    refresh();
    
    if (meteringMode == 0) {
      // Ambient light meter mode.
      lightMeter.configure(BH1750::ONE_TIME_HIGH_RES_MODE_2);

      lux = getLux();
      rgb_sensor.getColorTemp();

      if (Overflow == 1) {
        delay(10);
        getLux();
      }

      refresh();
      delay(200);
    } else if (meteringMode == 1) {
      // Flash light metering
      lightMeter.configure(BH1750::CONTINUOUS_LOW_RES_MODE);

display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(15, 15);
display.print(F("METERING"));
display.setCursor(15, 35);
display.print(F("FLASH..."));
display.display();

      unsigned long startTime = millis();
      uint16_t currentLux = 0;
      lux = 0;

      while (true) {
        // check max flash metering time
        if (startTime + MaxFlashMeteringTime < millis()) {
          break;
        }

        currentLux = getLux();
        rgb_sensor.getColorTemp();
        delay(16);
        
        if (currentLux > lux) {
          lux = currentLux;
        }
      }
      refresh();
    }
  }
}

void outOfrange() {
  display.println(F("--"));
}

void SaveSettings() {

  // Save lightmeter setting into EEPROM.
  EEPROM.write(ISOIndexAddr, ISOIndex);
  EEPROM.write(modeIndexAddr, modeIndex);
  EEPROM.write(apertureIndexAddr, apertureIndex);
  EEPROM.write(T_expIndexAddr, T_expIndex);
  EEPROM.write(meteringModeAddr, meteringMode);
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
}

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

/* nd */

// Calculate new exposure value and display it.
void refresh() {
  ISOset = false;
  Screen = true;

  float EV = lux2ev(lux);
  float T = getTimeByIndex(T_expIndex);
  float A = getApertureByIndex(apertureIndex);
  long  iso = getISOByIndex(ISOIndex);

 /* nd */
 
  if (ISOND = iso)

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


void ISOSpeed() {
  ISOset = true;
  Screen = false;

// ISO SPEED SET
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 57);
  display.println(F("SET:    "));
  
  long iso = getISOByIndex(ISOIndex);

  display.setCursor(24, 57);
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
  delay(200);
}


/* /////// FUNCTION /////// */

  void menu() {
  if (!Bn1 && !Bn2) {
    if (Screen) {
      ISOSpeed();
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
      ISOSpeed();
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
