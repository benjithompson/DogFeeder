/*
  This a simple example of the aREST Library for the ESP32 WiFi chip.
  See the README file for more details.
  Written in 2017 by Marco Schwartz under a GPL license.
  
*/

// Import required libraries
#include <WiFi.h>
#include <aREST.h>
#include "FeederPrefs.h"
#include "Feeder.h"
#include "WifiConfig.h"

#define LIGHTPIN 2

aREST rest = aREST();
WiFiServer server(NETWORK_PORT);


// Declare local functions
void connectWifi();
void wifiConnectPending();


void setup()
{

    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
    digitalWrite(25, LOW);

    pullPreferences();
    printPrefs();

    // Variables to be exposed
    rest.variable("breakfastTime", &breakfastTime);
    rest.variable("dinnerTime", &dinnerTime);
    rest.variable("feedCups", &feedCups);

    // Functions to be exposed
    rest.function("led", ledControl);
    rest.function("stopFeed", stopFeed);
    rest.function("startFeed", startFeed);
    rest.function("setFeedRPM", setFeedRPM);

    rest.function("setFeedCups", setFeedCups);
    rest.function("setDinnerTime", setDinnerTime);
    rest.function("setBreakfastTime", setBreakfastTime);

    rest.function("resetPreferences", resetPreferences);
    rest.function("restartFeeder", restartFeeder);
    rest.function("isFeeding", getIsFeeding);

    // Give name & ID to the device (ID should be 6 characters long)
    rest.set_id("000001");
    rest.set_name("DogFeeder");

    //Stepper default Setup
    getStepper().setRpm(feedRPM);

    Serial.printf("Stepper RPM: %d\n", getStepper().getRpm());
    Serial.printf("Stepper delay(microsec): %d\n",getStepper().getDelay());

    // Connect to WiFi
    connectWifi();

    // Start the server
    server.begin();
    Serial.println("Server started");
}

void loop()
{

    
    if(getStepper().getStepsLeft() == 0 && getIsFeeding("") == 1) {
        Serial.printf("Done feeding.\n");
        setIsFeeding(0);
        digitalWrite(14, LOW);
        digitalWrite(27, LOW);
        digitalWrite(26, LOW);
        digitalWrite(25, LOW);
    }
    // Handle REST calls
    WiFiClient client = server.available();

    // if(restartRequested==1){
    //     Serial.println("restartComplete");
    //     client.println("HTTP/1.1 200 OK");
    //     setRestartRequested(0);
    // }
    if (!client)
    {
        return;
    }
    while (!client.available())
    {
        delay(1);

    }
    rest.handle(client);

    
}

//Local functions
void wifiConnectPending()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        //Serial.print(".");
    }

    //Blink LED when connected
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
    }
    // Print the IP address
    Serial.print("WiFi connected: ");
    Serial.println(WiFi.localIP());
}

void connectWifi()
{
    // Connect to WiFi
    WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);
    Serial.println("Connecting to Wifi...");
    wifiConnectPending();
}
