#include <Arduino.h>
#include <Metro.h>
#include <Servo.h>

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

Servo *servoList[NUM_SERVO] = {&FLL_Servo, &FLR_Servo, &FRL_Servo, &FRR_Servo,
                               &BLL_Servo, &BLR_Servo, &BRL_Servo, &BRR_Servo};

Metro driveMetro = Metro(50);

void setup() {

    pinMode(LED_BUILTIN, OUTPUT);

    FLL_Servo.attach(FLL_PIN);
    FLR_Servo.attach(FLR_PIN);
    FRL_Servo.attach(FRL_PIN);
    FRR_Servo.attach(FRR_PIN);
    BLL_Servo.attach(BLL_PIN);
    BLR_Servo.attach(BLR_PIN);
    BRL_Servo.attach(BRL_PIN);
    BRR_Servo.attach(BRR_PIN);

}

uint8_t deg = 80;

void loop() {

    if (driveMetro.check() == 1)
    {
        digitalWriteFast(LED_BUILTIN, !digitalReadFast(LED_BUILTIN));

        for (uint8_t i = 0; i < NUM_SERVO; i++)
        {
            servoList[i]->write(deg);
        }
    }
    
}