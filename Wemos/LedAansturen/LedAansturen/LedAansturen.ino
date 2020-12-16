#include <Wire.h>
#include <Servo.h>
#include "ESP8266WiFi.h"

const char* ssid = "MARKO";
const char* password = "microsoft";



int status = WL_IDLE_STATUS;
IPAddress server(192, 168, 137, 63);

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


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
