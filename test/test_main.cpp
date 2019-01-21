
#include <Arduino.h>
#include <WiFi.h>
#include <aREST.h>
#include "FeederPrefs.h"
#include "Feeder.h"
#include "WifiConfig.h"
#include <unity.h>

Preferences preferences;

// void setUp(void) {
// // set stuff up here
    
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(LED_BUILTIN, 2);
}

void test_led_state_high(void) {
    digitalWrite(LED_BUILTIN, HIGH);
    TEST_ASSERT_EQUAL(digitalRead(LED_BUILTIN), HIGH);
}

void test_led_state_low(void) {
    digitalWrite(LED_BUILTIN, LOW);
    TEST_ASSERT_EQUAL(digitalRead(LED_BUILTIN), LOW);
}

void test_pref_int(void){
    preferences.begin("testpref", false);
    preferences.putInt("testInt", 1000);
    int pref = preferences.getInt("testInt");
    preferences.end();
    TEST_ASSERT_EQUAL(pref, 1000);
}

void test_pref_double(void){
    preferences.begin("testpref", false);
    preferences.putDouble("testDouble", 2.5);
    double pref = preferences.getDouble("testDouble");
    preferences.end();
    TEST_ASSERT_EQUAL(pref, 2.5);
}


void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    //delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);

    pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t i = 0;
uint8_t max_blinks = 2;

void loop() {
    if (i < max_blinks)
    {
        RUN_TEST(test_led_state_high);
        delay(50);
        RUN_TEST(test_led_state_low);
        delay(50);
        i++;
    }

    RUN_TEST(test_pref_int);
    RUN_TEST(test_pref_double);

    UNITY_END();


    



}