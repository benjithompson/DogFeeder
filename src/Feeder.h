#ifndef FEEDER_H
#define FEEDER_H
#include <CheapStepper.h>
#include "FeederPrefs.h"


CheapStepper getStepper();
int getIsFeeding(String command);
int setIsFeeding(int status);
int startFeedCups(String command);
int startFeedDegrees(String command);
int stopFeed(String command);
int setFeedRPM(String command);
int ledControl(String command);
int restartFeeder(String command);
int cupsToDegrees(double cups);

#endif

