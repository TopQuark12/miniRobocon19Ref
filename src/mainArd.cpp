#include <Arduino.h>
#include <Metro.h>
#include <Servo.h>
#include "kinmatics.hpp"
#include "gait.h"

#define TICK_MS     100

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

Leg FLLeg = Leg(FLL_Servo, FLR_Servo, legParam);
Leg FRLeg = Leg(FRL_Servo, FRR_Servo, legParam);
Leg BLLeg = Leg(BLL_Servo, BLR_Servo, legParam);
Leg BRLeg = Leg(BRL_Servo, BRR_Servo, legParam);

Metro driveMetro = Metro(TICK_MS);

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
gait_e currentGait = RESET;

void loop() {

    // if (driveMetro.check())
    // {
    //     digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));
    //     calcSuccess = FLLeg.travel(-x, y);
    //     calcSuccess = FRLeg.travel(-x, y);
    //     calcSuccess = BLLeg.travel(-x, y);
    //     calcSuccess = BRLeg.travel(-x, y);
    // }

    // for (int i = 0; i < gaitResolution; i++)
    // {
    //     while(!driveMetro.check()) {}
    //     FLLeg.travel(gaitX[(i + 12) % gaitResolution], gaitY[(i + 12) % gaitResolution]);
    //     FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
    //     BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
    //     BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
    // }
    // while(!driveMetro.check()) {}

    if (driveMetro.check())
    {
        static int i = 0;
        if (i >= gaitResolution)
            i = 0;
        if (i < 0)
            i = gaitResolution;
        switch (currentGait){

            case RESET:
                FLLeg.reset();
                FRLeg.reset();
                BLLeg.reset();
                BRLeg.reset();
                break;

            case BACKWARD:
                FLLeg.travel(gaitX[(i + 12) % gaitResolution], gaitY[(i + 12) % gaitResolution]);
                FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
                BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
                BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                i++;
                break;

            case FORWARD:
                FLLeg.travel(gaitX[(i + 12) % gaitResolution], gaitY[(i + 12) % gaitResolution]);
                FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
                BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
                BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                i--;
                break;

            case RIGHT:
                FLLeg.travel(0, 0.075);
                FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
                BLLeg.travel(0, 0.075);
                BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                i--;
                break;

            case LEFT:
                FLLeg.travel(0, 0.075);
                FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
                BLLeg.travel(0, 0.075);
                BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                i++;
                break;

            case CLIMBING:
                x = 0.02;
                y = 0.095;
                static bool proceed;
                proceed = false;
                calcSuccess = FLLeg.travel(x, y);
                calcSuccess = FRLeg.travel(x, y);
                calcSuccess = BLLeg.travel(0, y - 0.02);
                calcSuccess = BRLeg.travel(0, y );
                delay(TICK_MS * 7);
                // while (!proceed) {}
                // proceed = false;
                static float gaitYUpLift = 0.06;
                static float gaitXUpTravel = 0.017;
                calcSuccess = FRLeg.travel(gaitXUpTravel, 0.04);
                delay(TICK_MS * 7);
                calcSuccess = FRLeg.travel(-gaitXUpTravel, 0.04);
                delay(TICK_MS * 7);
                calcSuccess = FRLeg.travel(-0.025, gaitYUpLift);
                delay(TICK_MS * 7);
                calcSuccess = FRLeg.travel(-0.04, 0.08);
                delay(TICK_MS * 7);
                // while (!proceed) {}
                // proceed = false;

                // calcSuccess = BLLeg.travel(0.02, y - 0.02);
                // calcSuccess = BRLeg.travel(0.02, y);
                // delay(TICK_MS * 10);

                calcSuccess = BRLeg.travel(0.0, y - 0.02);
                delay(TICK_MS * 7);
                calcSuccess = BLLeg.travel(0.0, y - 0.01);
                delay(TICK_MS * 7);

                // while (!proceed) {}
                // proceed = false;

                calcSuccess = FLLeg.travel(-0.012, 0.045);
                delay(TICK_MS * 7);
                calcSuccess = FLLeg.travel(-0.04, 0.08);
                delay(TICK_MS * 7);
                // while (!proceed) {}
                // proceed = false;

                for (int i = 10; i > 0; i --) 
                {
                    BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
                    BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                    delay(TICK_MS);
                }

                // calcSuccess = FLLeg.travel(0, 0.02);
                // calcSuccess = FRLeg.travel(0, 0.02);
                //delay(TICK_MS * 7);

                for (int i = 40; i > 0; i--)//60
                {
                    BLLeg.travel(gaitX[(i + 8) % gaitResolution], gaitY[(i + 8) % gaitResolution]);
                    BRLeg.travel(gaitX[(i + 0) % gaitResolution], gaitY[(i + 0) % gaitResolution]);
                    FLLeg.travel(gaitXclimb[(i + 12) % gaitResolution], gaitYclimb[(i + 12) % gaitResolution]);
                    FRLeg.travel(gaitXclimb[(i + 4) % gaitResolution], gaitYclimb[(i + 4) % gaitResolution]);
                    delay(TICK_MS);
                }

                // BLLeg.reset();
                // BRLeg.reset();

                // for (int i = 16; i > 0; i--)
                // {
                //     FLLeg.travel(gaitX[(i + 12) % gaitResolution], gaitY[(i + 12) % gaitResolution]);
                //     FRLeg.travel(gaitX[(i + 4) % gaitResolution], gaitY[(i + 4) % gaitResolution]);
                //     delay(TICK_MS);
                // }

                x = 0.0;
                y = 0.09;
                calcSuccess = FLLeg.travel(-x, y - 0.03);
                calcSuccess = FRLeg.travel(-x, y - 0.03);
                calcSuccess = BLLeg.travel(-x, y);
                calcSuccess = BRLeg.travel(-x, y);

                for (int i = 16; i > 0; i--)
                {
                    FLLeg.travel(gaitXclimb[(i + 8) % gaitResolution], gaitYclimb[(i + 8) % gaitResolution]);
                    FRLeg.travel(gaitXclimb[(i + 0) % gaitResolution], gaitYclimb[(i + 0) % gaitResolution]);
                    
                    delay(TICK_MS);
                }
                delay(TICK_MS * 7);

                FLLeg.travel(-0.01, 0.06);
                FRLeg.travel(-0.01, 0.09);
                BLLeg.travel(-0.0, 0.07);
                delay(TICK_MS * 10);
                FLLeg.travel(-0.01, 0.05);
                delay(TICK_MS * 7);

                calcSuccess = BRLeg.travel(0.02, 0.05);
                delay(TICK_MS * 7);
                calcSuccess = BRLeg.travel(-0.06, 0.06);
                delay(TICK_MS * 7);
                // calcSuccess = BRLeg.travel(-0.05, 0.08);
                // delay(TICK_MS * 7);

                // while (!proceed) {}
                // proceed = false;

                FLLeg.travel(-0.02, 0.09);
                FRLeg.travel(-0.01, 0.055);
                delay(TICK_MS * 7);
                BLLeg.travel(-0.0, 0.092);
                delay(TICK_MS * 10);

                BLLeg.travel(0, 0.05);
                delay(TICK_MS * 7);
                BLLeg.travel(-0.07, 0.07);
                delay(TICK_MS * 7);

                FLLeg.reset();
                FRLeg.reset();
                BLLeg.reset();
                BRLeg.reset();

                // while (!proceed) {
                //     //calcSuccess = FLLeg.travel(x, y);
                // }
                proceed = false;
                currentGait = FORWARD;
                break;
        }
    }

}

