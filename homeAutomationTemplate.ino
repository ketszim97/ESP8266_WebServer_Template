#include <ESP8266Wifi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#define DEBUG 1               //Used to enable debugging mode in which serial outputs are included. Comment out to disable Serial. "Code Scaffolding"

const int led = 13;
const char* ssid = "your_ssid_here";
const char* password = "your_password_here";

ESP8266WebServer server (80);                //Create a webserver object on port 80 (default http port)

void handleRoot() {
     server.send(200, "text/plain", "This is the root directory");              //Return a 200 (OK) status code and send a simple text string
     #ifdef DEBUG
          Serial.println("Root Request");
     #endif
}

void handleNotFound() {
     server.send(404, "text/plain", "Error 404: Not Found");               //Return a 404 (Not Found) status code and send a simple text string
     #ifdef DEBUG
          Serial.println("Not Found: 404 Error");
     #endif
}

void handleOn() {
     server.send(200, "text/plain", "LED On");              //Return a 200 (OK) status code and send a simple text string
     digitalWrite(led, 0);              //Turn on active low LED
     #ifdef DEBUG
          Serial.println("On Request");
     #endif
}

void handleOff() {
     server.send(200, "text/plain", "LED Off");             //Return a 200 (OK) status code and send a simple text string
     digitalWrite(led, 1);              //Turn off active low LED
     #ifdef DEBUG
          Serial.println("Off Request");
     #endif
}


void setup(void) {
     pinMode(led, OUTPUT);              //Configure the built in LED as an output
     WiFi.mode(WIFI_STA);
     WiFi.begin(ssid, password);
     #ifdef DEBUG
          Serial.begin(9600);           //Enable UART with baudrate 9600 baud
          while (WiFi.status() != WL_CONNECTED){            //Wait untill WiFi manages to successfully connect
               delay(500);
               Serial.print(".");
          }
          Serial.println(WiFi.localIP());              //Print the local IP of the ESP8266 upon connection
     #endif

     server.onNotFound(handleNotFound);
     server.on("/", handleRoot);                      //Handle any requests to the server root
     server.on("/on", handleOn);                      //Turn on the LED by calling handleOn function
     server.on("/off", handleOff);                    //This template can be used to increase the number of functions

     server.begin();
     #ifdef DEBUG
          Serial.println("Server Started");
     #endif
}

void loop(void) {
     server.handleClient();
}
