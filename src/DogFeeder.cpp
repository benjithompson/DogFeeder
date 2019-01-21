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

    // Start Serial
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    
    //FeederPrefs fp("feeder_prefs");
    breakfastTime = prefs.getInt("breakfastTime", -1);
    dinnerTime = prefs.getInt("dinnerTime", -1);
    feedCups = prefs.getDouble("feedCups", 0.0);

    printPrefs();

    rest.variable("breakfastTime", &breakfastTime);
    rest.variable("dinnerTime", &dinnerTime);
    rest.variable("feedCups", &feedCups);
    rest.variable("isFeeding", &isFeeding);

    // Function to be exposed
    rest.function("led", ledControl);
    rest.function("stopFeed", stopFeed);
    rest.function("startFeed", startFeed);
    rest.function("setFeedCups", setFeedCups);
    rest.function("setDinnerTime", setDinnerTime);
    rest.function("setBreakfastTime", setBreakfastTime);
    rest.function("resetPreferences", resetPreferences);

    // Give name & ID to the device (ID should be 6 characters long)
    rest.set_id("000001");
    rest.set_name("DogFeeder");

    // Connect to WiFi
    connectWifi();

    // Start the server
    server.begin();
    Serial.println("Server started");

    /* Close the Preferences */
    prefs.end();
}

void loop()
{

    // Handle REST calls
    WiFiClient client = server.available();
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
