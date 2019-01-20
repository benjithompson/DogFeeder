/*
  This a simple example of the aREST Library for the ESP32 WiFi chip.
  See the README file for more details.
  Written in 2017 by Marco Schwartz under a GPL license.
  
*/

// Import required libraries
#include <WiFi.h>
#include <aREST.h>
#include "WifiConfig.h"

// Create aREST instance
aREST rest = aREST();

// Create an instance of the server
WiFiServer server(NETWORK_PORT);

// Variables to be exposed to the API
int breakfastTime;
int dinnerTime;
double feedCups;


// Declare functions to be exposed to the API
int startFeed(String command);
int stopFeed(String command);
int setBreakfastTime(String command);
int setDinnerTime(String command);
int setFeedCups(String command);
int isFeeding(String command);
int ledControl(String command);

void setup()
{
  
  // Start Serial
  Serial.begin(115200);

  // Init variables and expose them to REST API
  breakfastTime = -1;
  dinnerTime = -1;
  feedCups = 1;
  rest.variable("breakfastTime",&breakfastTime);
  rest.variable("dinnerTime",&dinnerTime);
  rest.variable("feedCups", &feedCups);

  // Function to be exposed
  rest.function("led",ledControl);
  rest.function("startFeed", startFeed);
  rest.function("stopFeed", stopFeed);
  rest.function("setBreakfastTime", setBreakfastTime);
  rest.function("setDinnerTime", setDinnerTime);
  rest.function("setFeedCups", setFeedCups);
  rest.function("isFeeding", isFeeding);
  rest.function("ledControl", ledControl);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("000001");
  rest.set_name("esp32");

  // Connect to WiFi
  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

// Custom function accessible by the API

int startFeed(String command){
    return 1;
}
int stopFeed(String command){
    return 1;
}
int setBreakfastTime(String command){
    return 1;
}

int setDinnerTime(String command){
    return 1;
}

int setFeedCups(String command){
    return 1;
}

int isFeeding(String command){
    return 1;
}

int ledControl(String command) {
    // Get state from command
    int state = command.toInt();

    digitalWrite(6,state);
    return 1;
}
