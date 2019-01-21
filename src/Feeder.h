#ifndef FEEDER_H
#define FEEDER_H
#include <CheapStepper.h>

extern int isFeeding;

int startFeed(String command);
int stopFeed(String command);
int ledControl(String command);
int restartFeeder(String command);

#endif

