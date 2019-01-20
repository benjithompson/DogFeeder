/*
  This a simple example of the aREST Library for the ESP32 WiFi chip.
  See the README file for more details.
  Written in 2017 by Marco Schwartz under a GPL license.
  
*/

// Import required libraries
#include <WiFi.h>
#include <aREST.h>
#include <Preferences.h>
#include "WifiConfig.h"

#define LIGHTPIN 2

// create an instance of Preferences library
Preferences preferences;

// Create aREST instance
aREST rest = aREST();

// Create an instance of the server
WiFiServer server(NETWORK_PORT);

// Variables to be exposed to the API
int breakfastTime;
int dinnerTime;
double feedCups;
int isFeeding;

// Declare functions to be exposed to the API
int startFeed(String command);
int stopFeed(String command);
int setBreakfastTime(String command);
int setDinnerTime(String command);
int setFeedCups(String command);
int ledControl(String command);
int resetPreferences(String command);
// Declare local functions
void connectWifi();
void wifiConnectPending();
void printCurrentPrefs();

void setup()
{

    // Start Serial
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    /* Start a namespace "feedpref"
    in Read-Write mode: set second parameter to false 
    Note: Namespace name is limited to 15 chars */
    preferences.begin("feedpref", true);

    // Init variables from stored Preferences key:value pairs and expose them to REST API. If none exist
    // use the default value
    breakfastTime = preferences.getInt("breakfastTime", -1);
    dinnerTime = preferences.getInt("dinnerTime", -1);
    feedCups = preferences.getDouble("feedCups", 0.0);
    isFeeding = 0;

    printCurrentPrefs();

    rest.variable("breakfastTime", &breakfastTime);
    rest.variable("dinnerTime", &dinnerTime);
    rest.variable("feedCups", &feedCups);
    rest.variable("isFeeding", &isFeeding);

    // Function to be exposed
    rest.function("led", ledControl);
    rest.function("startFeed", startFeed);
    rest.function("stopFeed", stopFeed);
    rest.function("setBreakfastTime", setBreakfastTime);
    rest.function("setDinnerTime", setDinnerTime);
    rest.function("setFeedCups", setFeedCups);
    rest.function("ledControl", ledControl);
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
    preferences.end();
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

// Custom function accessible by the API

int startFeed(String command)
{
    //Start motor for the number of set cups
    return 1;
}
int stopFeed(String command)
{
    //Stop feeding by stopping motor
    return 1;
}
int setBreakfastTime(String command)
{
    int cmd = command.toInt();
    Serial.printf("Current Breakfast Time: %d\n", breakfastTime);
    preferences.begin("feedpref", false);
    preferences.putInt("breakfastTime", cmd);
    breakfastTime = preferences.getInt("breakfastTime", -1);
    Serial.printf("New Breakfast Time: %d\n", breakfastTime);
    preferences.end();
    return breakfastTime;
}

int setDinnerTime(String command)
{
    int cmd = command.toInt();
    Serial.printf("Current dinner Time: %d\n", dinnerTime);
    preferences.begin("feedpref", false);
    preferences.putInt("dinnerTime", cmd);
    dinnerTime = preferences.getInt("dinnerTime", -1);
    Serial.printf("New dinner Time: %d\n", dinnerTime);
    preferences.end();
    return dinnerTime;
}

int setFeedCups(String command)
{
    double cmd = command.toDouble();
    Serial.printf("Current Feed Cups: %.1f\n", feedCups);
    preferences.begin("feedpref", false);
    preferences.putDouble("feedCups", cmd);
    feedCups = preferences.getDouble("feedCups", -1);
    Serial.printf("New Feed Cups: %.1f\n", feedCups);
    preferences.end();
    return feedCups;
}

int ledControl(String command)
{
    // Get state from command
    int state = command.toInt();

    digitalWrite(6, state);
    return 1;
}

int resetPreferences(String command)
{
    Serial.println("Reset Preferences");
    preferences.begin("feedpref", false);
    preferences.clear();
    breakfastTime = preferences.getInt("breakfastTime", -1);
    dinnerTime = preferences.getInt("dinnerTime", -1);
    feedCups = preferences.getDouble("feedCups", 0.0);
    preferences.end();

    return 1;
}

//Local private functions

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

void printCurrentPrefs()
{
    printf("breakfastTime: %d\n", breakfastTime);
    printf("dinnerTime: %d\n", dinnerTime);
    printf("feedCups: %.1f\n", feedCups);
}