#include "Feeder.h"

#define VOLUMNCONSTANT 900

CheapStepper stepper(14,27,26,25);
int isFeeding = 0;

CheapStepper getStepper(){
    return stepper;
}

int getIsFeeding(String command){
    return isFeeding;
}

//starts stepper move with integer cups.
int startFeedCups(String command)
{
    int cups = command.toInt();
    int degrees = cupsToDegrees(cups);
    String sDegrees = String(degrees);
    startFeedDegrees(sDegrees);
    return cups;
}

//starts stepper move with integer degrees.
int startFeedDegrees(String command)
{
    int degrees = command.toInt();

    if(degrees >= 0){
        Serial.printf("moveDegreesCW: %d\n", degrees);
        stepper.moveDegreesCW(degrees);
    }else{
        Serial.printf("moveDegreesCCW: %d\n", -degrees);
        stepper.moveDegreesCCW(-degrees);
    }

    setIsFeeding(1);
    return degrees;
}

int stopFeed(String command)
{
    stepper.stop();
    return 1;
}

int setFeedRPM(String command){
    int rpm = command.toInt();
    stepper.setRpm(rpm);
    setFeedRPMPref(rpm);
    return rpm;
}

int ledControl(String command)
{
    // Get state from command
    int state = command.toInt();

    digitalWrite(6, state);
    return state;
}

int restartFeeder(String command){
    setRestartRequested(1);
    ESP.restart();
    return 1;
}

int cupsToDegrees(double cups){
    //cups to degrees function
    return (int)(cups*VOLUMNCONSTANT);
}

int setStepperRPM(int rpm){
    getStepper().setRpm(rpm);
}

int setIsFeeding(int status){
    Serial.printf("startFeeding: %d\n", isFeeding);
    isFeeding = status;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    return isFeeding;
}