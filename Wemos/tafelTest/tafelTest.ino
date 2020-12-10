#include <Wire.h>
#include <Servo.h>
#include "ESP8266WiFi.h"
#include <Adafruit_NeoPixel.h>

#define PIN            D5
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // delay for 100ms for neopixel refresh

//   0x36    i2c address MAX11647
//   0x38    i2c address PCA9554A
int ADDRESS0 = 0x36;  //Analog inputs
int ADDRESS1 = 0x38;  //DI0-DI7


unsigned int output = 0x01;      // set outputs DIO4-DIO7   tintedwindow connected to DIO4
int input = 0;



void setup() {


  Serial.begin(9600);
  Wire.begin();
  pixels.begin();
  pinMode(D5, OUTPUT);

  
 




}

void loop() {

  pixels.setPixelColor(0, pixels.Color(255, 0, 0 ));
  pixels.show();
  delay(delayval);


  //Config PCA9554
  //DIO0-DIO3 as input, DIO4-DIO7 as output.
  Wire.beginTransmission(ADDRESS1);
  Wire.write(byte(0x03));          //DDR 0X03 CHOOSE input or output
  Wire.write(byte(0x0F));          // 00001111   1= INPUT 0=OUTPUT
  Wire.endTransmission();

  //Set PCA9554 outputs (DIO4-DIO7)
  Wire.beginTransmission(ADDRESS1);
  Wire.write(byte(0x01));        //  Hex adress to set output
  Wire.write(byte(output << 4));   // set the output
  Wire.endTransmission();
 // Serial.print("Digital out: ");
 // Serial.println(output & 0x0F);


  //Read PCA9554 inputs (DIO0-DIO3)
  Wire.beginTransmission(ADDRESS1);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  Serial.print("Digital in: ");
  Serial.println(inputs & 0x0F);
  input = inputs & 0x0f;



 








}
