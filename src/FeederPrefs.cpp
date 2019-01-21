#include "FeederPrefs.h"

  Preferences prefs;
  int breakfastTime;
  int dinnerTime;
  double feedCups;

int setBreakfastTime(String command)
{
    int cmd = command.toInt();
    Serial.printf("Current Breakfast Time: %d\n", breakfastTime);
    prefs.begin("feedpref", false);
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
    prefs.begin("feedpref", false);
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
    prefs.begin("feedpref", false);
    prefs.putDouble("feedCups", cmd);
    feedCups = prefs.getDouble("feedCups", -1);
    Serial.printf("New Feed Cups: %.1f\n", feedCups);
    prefs.end();
    return feedCups;
}

int resetPreferences(String command)
{
    Serial.println("Reset Preferences");
    prefs.begin("feedpref", false);
    prefs.clear();
    breakfastTime = prefs.getInt("breakfastTime", -1);
    dinnerTime = prefs.getInt("dinnerTime", -1);
    feedCups = prefs.getDouble("feedCups", 0.0);
    prefs.end();

    return 1;
}

void printPrefs()
{
    printf("breakfastTime: %d\n", breakfastTime);
    printf("dinnerTime: %d\n", dinnerTime);
    printf("feedCups: %.1f\n", feedCups);
}
