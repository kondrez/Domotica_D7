
#include "ESP8266WiFi.h"

const char* ssid = "MARKO";
const char* password = "microsoft";



int status = WL_IDLE_STATUS;
IPAddress server(192, 168, 137, 244);

// Initialize the client library
WiFiClient client;

char c;


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  delay(1000);



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




  if (client) {

    while (client.connected()) {

      while (client.available() > 0) {
         c = client.read();
        Serial.write(c);


     if (c == '0'){
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if (c == '1'){
        digitalWrite(LED_BUILTIN, LOW);
      }

     


      }


      //client.stop();
      // Serial.println("Server disconnected");


     // client.write("Hello im the wemos");
   

    //  Serial.println("Sended");
    }





  }


}
