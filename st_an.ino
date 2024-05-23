#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according
byte celsius[8] = {  0x00, 0x0E,  0x0A,  0x0E,  0x00,  0x00,  0x00, 0x00 };

#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C

void setup() {
  
  Serial.begin(9600);

  dht.begin();

  lcd.begin(false); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  lcd.backlight();  //back light on
  lcd.createChar(1, celsius); 

  unsigned status;
  status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


}

void loop() { 


  int hum = dht.readHumidity();
  float temp = bmp.readTemperature();
  if (isnan(hum) || isnan(temp)) { // Is Not A Number
    hum = 51;
    temp = 23.4;
  }
  char sHum[16] = "";
  char sTemp[16] = "";
  char fTemp[16];

  char spress[16] = "";
  char fpress[16];

  dtostrf(temp,4,1,fTemp);
  sprintf(sTemp, "T:%s%cC ", fTemp, 1 );  //byte(1)   0x01  ascii 1
  
 float press = bmp.readPressure();
 
 dtostrf(press,4,1,fpress);
 sprintf(spress, "P:%s Pa ", fpress);  
  
  sprintf(sHum, "H:%2d%%  ", hum);

  lcd.clear();
  lcd.setCursor(0, 0); //  setting the cursor in the desired position.
  lcd.print(sTemp);
  lcd.print(sHum);
  // lcd.write(byte(1)); 
  // lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(spress);


  Serial.println(sTemp);
  Serial.println(spress);
  Serial.println(sHum);
  
  delay(2000);

}


