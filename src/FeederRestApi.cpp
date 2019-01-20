/*
    FeederRestAPI.cpp - Library for REST API functions to control Dog Feeder motor and store scheduling info
*/

#include "FeederRestApi.h"
#include <Arduino.h>

class FeederRestApi {

    aREST _rest;

    //Constructor
    FeederRestApi(){

         _rest = aREST();
         _rest.function("test0", testFunction0);
         _rest.function("test1", testFunction1);
    }
    
    //Getters
    aREST getARestApi(){
        return _rest;
    }

    //Setters


    //Methods
    static int testFunction0(String command) {
        Serial.println("0Received rest request");
        Serial.println(command);
    }

    static int testFunction1(String command) {
        Serial.println("1Received rest request");
        Serial.println(command);
    }

};




