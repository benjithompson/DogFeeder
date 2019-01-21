#include "Feeder.h"

CheapStepper stepper(14,27,26,25);
int isFeeding = 0;

CheapStepper getStepper(){
    return stepper;
}

int getIsFeeding(String command){
    return isFeeding;
}

int setIsFeeding(int status){
    isFeeding = status;
}

int startFeed(String command)
{
    int degrees = command.toInt();

    if(degrees == 0){
        degrees = cupsToDegrees(feedCups);
    }
    Serial.printf("degrees: %d\n", degrees);
    setIsFeeding(1);
    Serial.printf("startFeeding: %d\n", isFeeding);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    //convert feedcups to degrees
    stepper.moveDegreesCW(degrees);

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
    int degrees = (int)cups;
    return degrees;
}

int setStepperRPM(int rpm){
    getStepper().setRpm(rpm);
}