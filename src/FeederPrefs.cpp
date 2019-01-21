#include "FeederPrefs.h"

  Preferences prefs;
  int breakfastTime;
  int dinnerTime;
  double feedCups;
  int feedRPM;
  int restartRequested;

void pullPreferences()
{
    prefs.begin("feedprefs");
    breakfastTime = prefs.getInt("breakfastTime", -1);
    dinnerTime = prefs.getInt("dinnerTime", -1);
    feedCups = prefs.getDouble("feedCups", 0.0);
    feedRPM = prefs.getInt("feedRPM", 12);
    restartRequested = prefs.getInt("restartReq", 0);
    prefs.end();
}

int setBreakfastTime(String command)
{
    int cmd = command.toInt();
    Serial.printf("Current Breakfast Time: %d\n", breakfastTime);
    prefs.begin("feedprefs", false);
    prefs.putInt("breakfastTime", cmd);
    breakfastTime = prefs.getInt("breakfastTime", -1);
    Serial.printf("New Breakfast Time: %d\n", breakfastTime);
    prefs.end();
    return breakfastTime;
}

int setDinnerTime(String command)
{
    int cmd = command.toInt();
    Serial.printf("Current dinner Time: %d\n", dinnerTime);
    prefs.begin("feedprefs", false);
    prefs.putInt("dinnerTime", cmd);
    dinnerTime = prefs.getInt("dinnerTime", -1);
    Serial.printf("New dinner Time: %d\n", dinnerTime);
    prefs.end();
    return dinnerTime;
}

int setFeedCups(String command)
{
    double cmd = command.toDouble();
    Serial.printf("Current Feed Cups: %.1f\n", feedCups);
    prefs.begin("feedprefs", false);
    prefs.putDouble("feedCups", cmd);
    feedCups = prefs.getDouble("feedCups", -1);
    Serial.printf("New Feed Cups: %.1f\n", feedCups);
    prefs.end();
    return feedCups;
}

void setFeedRPMPref(int rpm){
    Serial.printf("Current RPM: %d\n", feedRPM);
    prefs.begin("feedprefs", false);
    prefs.putInt("feedRPM", rpm);
    feedRPM = prefs.getInt("feedRPM", 12);
    Serial.printf("New feedRPM: %d\n", feedRPM);
    prefs.end();
}

void setRestartRequested(int restartState)
{
    Serial.printf("Current restartRequested: %d\n", restartRequested);
    prefs.begin("feedprefs", false);
    prefs.putInt("restartReq", restartState);
    restartRequested = prefs.getInt("restartReq", 0);
    Serial.printf("New restartRequested: %d\n", restartRequested);
    prefs.end();
}

int resetPreferences(String command)
{
    Serial.println("Reset Preferences");
    prefs.begin("feedprefs", false);
    prefs.clear();
    breakfastTime = prefs.getInt("breakfastTime", -1);
    dinnerTime = prefs.getInt("dinnerTime", -1);
    feedCups = prefs.getDouble("feedCups", 0.0);
    restartRequested = prefs.getInt("restartReq", 0);
    prefs.end();
    return 1;
}

void printPrefs()
{
    printf("breakfastTime: %d\n", breakfastTime);
    printf("dinnerTime: %d\n", dinnerTime);
    printf("feedCups: %.1f\n", feedCups);
    printf("restartRequested: %d\n", restartRequested);
    printf("feedRPM: %d\n", feedRPM);
}
