#include "Feeder.h"

int isFeeding;

int getIsFeeding(){
    return 0;
}

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
int ledControl(String command)
{
    // Get state from command
    int state = command.toInt();

    digitalWrite(6, state);
    return 1;
}

int restartFeeder(String command){
    ESP.restart();
}