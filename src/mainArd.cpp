#include <Arduino.h>
#include <Metro.h>
#include <Servo.h>
#include "kinmatics.hpp"

#define NUM_SERVO   8

#define FLL_PIN     2
#define FLR_PIN     3
#define FRL_PIN     4
#define FRR_PIN     5
#define BLL_PIN     6
#define BLR_PIN     7
#define BRL_PIN     8
#define BRR_PIN     9

Servo FLL_Servo;
Servo FLR_Servo;
Servo FRL_Servo;
Servo FRR_Servo;
Servo BLL_Servo;
Servo BLR_Servo;
Servo BRL_Servo;
Servo BRR_Servo;

legParam_t testParam = {

    0,          //actuator distance
    0.05,       //length A1
    0.095,      //length A2
    0.05,       //length B1
    0.095       //lenght B2

};

Leg testLeg = Leg(FLL_Servo, FLR_Servo, testParam);

Metro driveMetro = Metro(50);

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);

    testLeg.attach(FLL_PIN, FLR_PIN);
    testLeg.reset();

}

uint8_t deg = 80;
float x = 0;
float y = 0.1;
bool calcSuccess;

void loop() {

    if (driveMetro.check() == 1)
    {
        digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
        calcSuccess = testLeg.travel(x, y);
    }
    
}