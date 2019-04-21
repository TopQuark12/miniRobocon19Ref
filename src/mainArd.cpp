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
    0.05,       //length A2
    0.05,       //length B1
    0.05        //lenght B2

};

Leg testLeg = Leg(FLL_Servo, FLR_Servo, testParam);

Metro driveMetro = Metro(100);

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);

    testLeg.attach(FLL_PIN, FLR_PIN);
    testLeg.reset();

}

float x = 0;
float y = 0.0707106;
bool calcSuccess;

const float gait[8][2] =
{
    {0.06, 0.07},
    {0.03, 0.07},
    {0.00, 0.07},
    {-0.03, 0.07},
    {-0.06, 0.07},
    {-0.03, 0.05},
    {0.00, 0.05},
    {0.03, 0.05} 
};

void loop() {

    // if (driveMetro.check())
    // {
    //     digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
    //     calcSuccess = testLeg.travel(x, y);
    // }

    for (int i = 0; i < 8; i++)
    {
        while(!driveMetro.check()) {}
        testLeg.travel(gait[i][0], gait[i][1]);
    }
    while(!driveMetro.check()) {}
}