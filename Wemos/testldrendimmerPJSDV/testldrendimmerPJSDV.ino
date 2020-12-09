#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN            D5
#define NUMPIXELS      3
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // delay for 100ms for neopixel refresh


//   0x36    i2c address MAX11647
//   0x38    i2c address PCA9554A
int ADDRESS0 = 0x36;  //Analog inputs
int ADDRESS1 = 0x38;  //DI0-DI7



unsigned int output = 0x01;      // set outputs DIO4-DIO7   tintedwindow connected to DIO4
unsigned int Brightness = 0;
unsigned int anin0;
unsigned int anin1;



void setup() {


  Serial.begin(9600);
  Wire.begin();
  pixels.begin();

  pinMode(D5, OUTPUT);




}

void loop() {



  pixels.setPixelColor(0, pixels.Color(Brightness, Brightness, Brightness));
  pixels.setPixelColor(1, pixels.Color(Brightness, Brightness, Brightness));
  pixels.setPixelColor(2, pixels.Color(Brightness, Brightness, Brightness));
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
  Serial.print("Digital out: ");
  Serial.println(output & 0x0F);


  //Read PCA9554 inputs (DIO0-DIO3)
  Wire.beginTransmission(ADDRESS1);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  Serial.print("Digital in: ");
  Serial.println(inputs & 0x0F);




  //Config MAX11647 Analog inputs
  Wire.beginTransmission(ADDRESS0);
  Wire.write(byte(0xA2));              //set-up byte
  Wire.write(byte(0x03));              //configuration byte
  Wire.endTransmission();
  // Read MAX11647
  Wire.requestFrom(0x36, 4);
  anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  anin1 = Wire.read() & 0x03;
  anin1 = anin1 << 8;
  anin1 = anin1 | Wire.read();
  Serial.print("analog in 0: ");
  Serial.println(anin0);
  Serial.print("analog in 1: ");
  Serial.println(anin1);
  Serial.println("");






}
