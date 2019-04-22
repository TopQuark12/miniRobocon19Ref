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

legParam_t legParam = {

    0,          //actuator distance
    0.05,       //length A1
    0.05,       //length A2
    0.05,       //length B1
    0.05        //lenght B2

};

Leg FLLeg = Leg(FLL_Servo, FLR_Servo, legParam);
Leg FRLeg = Leg(FRL_Servo, FRR_Servo, legParam);
Leg BLLeg = Leg(BLL_Servo, BLR_Servo, legParam);
Leg BRLeg = Leg(BRL_Servo, BRR_Servo, legParam);

Metro driveMetro = Metro(100);

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);

    FLLeg.attach(FLL_PIN, FLR_PIN);
    FLLeg.reset();

    FRLeg.attach(FRL_PIN, FRR_PIN);
    FRLeg.reset();

    BLLeg.attach(BLL_PIN, BLR_PIN);
    BLLeg.reset();

    BRLeg.attach(BRL_PIN, BRR_PIN);
    BRLeg.reset();
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

const uint8_t gaitResolution = 16;
const float gaitXWidth = 0.06;
const float gaitYUp = 0.05;
const float gaitYDown = 0.07;

//gaitX represents creep gait for forward / backward motion
float gaitX[gaitResolution] =
{
    -gaitXWidth,                            //beat 0
    -gaitXWidth,
    -gaitXWidth + (gaitXWidth * 2 / 3),
    gaitXWidth - (gaitXWidth * 2 / 3),
    gaitXWidth,                             //beat 1
    gaitXWidth,
    gaitXWidth - (gaitXWidth * 2 / 11) * 1,
    gaitXWidth - (gaitXWidth * 2 / 11) * 2,
    gaitXWidth - (gaitXWidth * 2 / 11) * 3, //beat 2
    gaitXWidth - (gaitXWidth * 2 / 11) * 4,
    gaitXWidth - (gaitXWidth * 2 / 11) * 5,
    gaitXWidth - (gaitXWidth * 2 / 11) * 6,
    gaitXWidth - (gaitXWidth * 2 / 11) * 7, //beat 3
    gaitXWidth - (gaitXWidth * 2 / 11) * 8,
    gaitXWidth - (gaitXWidth * 2 / 11) * 9,
    gaitXWidth - (gaitXWidth * 2 / 11) * 10
};

//gaitY represents creep gait for up / down motion
float gaitY[16] =
{
    gaitYDown,      //beat 0
    gaitYUp,
    gaitYUp,
    gaitYUp,
    gaitYDown,      //beat 1
    gaitYDown,
    gaitYDown,
    gaitYDown,
    gaitYDown,      //beat 2
    gaitYDown,
    gaitYDown,
    gaitYDown,
    gaitYDown,      //beat 3
    gaitYDown,
    gaitYDown,
    gaitYDown
};

void loop() {

    // if (driveMetro.check())
    // {
    //     digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
    //     calcSuccess = FLLeg.travel(-x, y);
    //     calcSuccess = FRLeg.travel(-x, y);
    //     calcSuccess = BLLeg.travel(-x, y);
    //     calcSuccess = BRLeg.travel(-x, y);
    // }

    for (int i = 0; i < gaitResolution; i++)
    {
        while(!driveMetro.check()) {}
        FLLeg.travel(gaitX[(i + 12) % gaitResolution], gaitY[(i + 12) % gaitResolution]);
        FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
        BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
        BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
    }
    while(!driveMetro.check()) {}
}

