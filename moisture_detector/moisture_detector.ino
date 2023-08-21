#include <Arduino.h>
#include <U8g2lib.h>
 
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
 
U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // SSD1306 and SSD1308Z are compatible
 
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);    //Low spped I2C

int sensorPinZero = A0;
int sensorPinOne = A1;
int sensorPinTwo = A2;
int sensorPinThree = A3;
int sensorValues[4];
bool happyPlants = true;
 
void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
}

int returnValue(int sensor){
  switch(sensor){
    case 0:
      return analogRead(sensorPinZero);
      break;
    case 1:
      return analogRead(sensorPinOne);
      break;
    case 2:
      return analogRead(sensorPinTwo);
      break;
    case 3:
      return analogRead(sensorPinThree);
      break;
  }
}

bool lowMoistCheck(void){
  for(int j = 0; j < 4; j++){
    if(sensorValues[j] < 90){
      Serial.println("SAD PLANTS!!!");
      return false;
    } else {
      Serial.print(j);
      Serial.println(" is a happy plant!");
    }
  }
}

 
void loop(void) {
  // sensorValue = analogRead(sensorPinOne);
  // char valueToScreen = sensorValue;
  // Serial.print("Moisture = " );
  // Serial.println(sensorValue);
  // u8g2.firstPage();
  // do{
  //   u8g2.setFont(u8g2_font_ncenB14_tr);
  //   u8g2.setCursor(0, 15);
  //   u8g2.print(sensorValue);
  // } while (u8g2.nextPage());
  // delay(1000);  
  for(int i = 0; i < 4 ; i++){
    sensorValues[i] = returnValue(i);
  }
  Serial.print("sensor 0:");
  Serial.println(sensorValues[0]);
  Serial.print("sensor 1:");
  Serial.println(sensorValues[1]);
  Serial.print("sensor 2:");
  Serial.println(sensorValues[2]);
  Serial.print("sensor 3:");
  Serial.println(sensorValues[3]);
  Serial.println("=============================================");
  
  u8g2.firstPage();

  if(!lowMoistCheck()){
    do{
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.setCursor(0, 15);
      u8g2.print("WATER" );
      u8g2.setCursor(0, 30);
      u8g2.print("PLANTS! :(");
    } while (u8g2.nextPage());

  } else {
    do{
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.setCursor(0, 15);
      u8g2.print(sensorValues[0]);
      u8g2.print(" ");
      u8g2.print(sensorValues[1]);
      u8g2.print(" ");
      u8g2.print(sensorValues[2]);
      u8g2.print(" ");
      u8g2.print(sensorValues[3]);
      u8g2.print(" ");


    } while (u8g2.nextPage());

  }

  delay(5000);
}
