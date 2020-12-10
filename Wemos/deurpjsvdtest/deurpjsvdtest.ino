#include <Wire.h>
#include <Servo.h>
#include "ESP8266WiFi.h"


const char* ssid = "MARKO";
const char* password = "microsoft";



int status = WL_IDLE_STATUS;
IPAddress server(192,168,137,63);  

// Initialize the client library
WiFiClient client;






Servo myservo;

//   0x36    i2c address MAX11647
//   0x38    i2c address PCA9554A
int ADDRESS0 = 0x36;  //Analog inputs
int ADDRESS1 = 0x38;  //DI0-DI7



unsigned int output = 0x01;      // set outputs DIO4-DIO7   tintedwindow connected to DIO4
int input = 0;



void setup() {


  Serial.begin(9600);
  Wire.begin();
  delay(1000);
  myservo.attach(D5);
  pinMode(D5, OUTPUT);

  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }

  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());



    if (client.connect(server, 8888)) {
      Serial.println("socket connected");
   

    }
 







}

void loop() {







  

//  if (client) {
//
//    while (client.connected()) {
//
//      while (client.available() > 0) {
//        char c = client.read();
//        Serial.write(c);  
//        
//      }
//
//      delay(10);
//    }
//
//    client.stop();
//    Serial.println("Server disconnected");
//
//  }






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
//  Serial.print("Digital in: ");
//  Serial.println(inputs & 0x0F);
  input = inputs & 0x0f;



  if (input == 13)
  {
    myservo.write(170);
    delay(2000);
  }

  if (input == 12) {
    myservo.write(82);

  }
  if (input == 14) {
    myservo.write(0);
    delay(2000);
  }








}
