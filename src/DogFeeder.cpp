/*
  DogFeeder Client Project. Takes rest requests to change configuration for feed schedule and feed amount.
  Motor control handles Stepper Motor functionality.
*/


#include <Arduino.h>
#include <WiFi.h>
#include "wifiConfig.h"
#include "FeederRestApi.h"


FeederRestApi feederapi = FeederRestApi();
aREST rest = feederapi.getARestApi();

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
    status = WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
    if ( status != WL_CONNECTED) { 
      Serial.println("Couldn't get a wifi connection");
      while(true);
    } 
    else {
      server.begin();
      Serial.print("Connected to wifi. My address:");
      IPAddress myAddress = WiFi.localIP();
      Serial.println(myAddress);
    }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    if (client.connected()) {
      Serial.println("Connected to client");
    }

    // close the connection:
    client.stop();
    rest.handle(client);
  }

}