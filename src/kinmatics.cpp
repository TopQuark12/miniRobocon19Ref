#include <Arduino.h>
#include "kinmatics.hpp"
#include <Servo.h>
#include <math.h>

void Leg::attach(uint8_t pinA, uint8_t pinB)
{
    servoA.attach((int)pinA);
    servoB.attach((int)pinB);
};

void Leg::reset()
{
    servoA.write(45);
    servoB.write(45);
};

bool Leg::travel(float x, float y)
{
    e[ACTUATOR_A] = -2 * param.lenLinkA1 * y;
    e[ACTUATOR_B] = -2 * param.lenLinkB1 * y;
    f[ACTUATOR_A] = -2 * param.lenLinkA1 * (x + param.lenActuatorDistance / 2);
    f[ACTUATOR_B] = -2 * param.lenLinkB1 * (x - param.lenActuatorDistance / 2);
    g[ACTUATOR_A] = (x + param.lenActuatorDistance / 2) * 
                    (x + param.lenActuatorDistance / 2) + 
                    y * y + 
                    param.lenLinkA1 * param.lenLinkA1 - 
                    param.lenLinkA2 * param.lenLinkA2;
    g[ACTUATOR_B] = (x - param.lenActuatorDistance / 2) *
                    (x - param.lenActuatorDistance / 2) +
                    y * y +
                    param.lenLinkB1 * param.lenLinkB1 -
                    param.lenLinkB2 * param.lenLinkB2;
    rad[ACTUATOR_A] = 2 * atan((-e[ACTUATOR_A] - sqrt(e[ACTUATOR_A] * e[ACTUATOR_A] - g[ACTUATOR_A] * g[ACTUATOR_A] + f[ACTUATOR_A] * f[ACTUATOR_A])) / (g[ACTUATOR_A] - f[ACTUATOR_A]));
    rad[ACTUATOR_B] = PI - 2 * atan((-e[ACTUATOR_B] + sqrt(e[ACTUATOR_B] * e[ACTUATOR_B] - g[ACTUATOR_B] * g[ACTUATOR_B] + f[ACTUATOR_B] * f[ACTUATOR_B])) / (g[ACTUATOR_B] - f[ACTUATOR_B]));
    
    if (rad[ACTUATOR_A] == INFINITY || rad[ACTUATOR_B] == INFINITY || isnan(rad[ACTUATOR_A]) || isnan(rad[ACTUATOR_B]))
        return 0;

    if (rad[ACTUATOR_A] >= 0 && rad[ACTUATOR_A] <= PI && rad[ACTUATOR_B] >= 0 && rad[ACTUATOR_B] <= PI)
    {
        deg[ACTUATOR_A] = rad[ACTUATOR_A] / PI * 180.0;
        deg[ACTUATOR_B] = rad[ACTUATOR_B] / PI * 180.0;
    }
    else
    {
        return 0;
    }
    
    servoA.write(deg[ACTUATOR_A]);
    servoB.write(deg[ACTUATOR_B]);
    return 1;
}

Leg::Leg(Servo &servoLeft, Servo &servoRight, legParam_t &param) :
    servoA(servoLeft),
    servoB(servoRight),
    param(param)
{

};

