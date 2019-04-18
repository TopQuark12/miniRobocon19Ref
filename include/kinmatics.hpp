#pragma once
#include <Servo.h>

typedef enum dimension_e
{
    X_AXIS = 0,
    Y_AXIS = 1

} dimension_e;

typedef enum actuator_e
{
    ACTUATOR_A = 0,
    ACTUATOR_B = 1
} actuator_e;

typedef struct legParam_t 
{

    float lenActuatorDistance;
    float lenLinkA1;
    float lenLinkA2;
    float lenLinkB1;
    float lenLinkB2;

} legParam_t;

class Leg
{
    public:
      //create
      Leg(Servo &servoLeft, Servo &servoRight, legParam_t &param);
      //attach servos
      void attach(uint8_t pinA, uint8_t pinB);
      //goto reset pos
      void reset();
      //move effector to requested position, return 1 if input is valid
      bool travel(float x, float y);    

    private:
      float effector[2];
      Servo servoA;
      Servo servoB;
      legParam_t param;
      float e[2];       //kinematic model element
      float f[2];       //kinematic model element
      float g[2];       //kinematic model element
      float rad[2];     //actuator angle in rad
      float deg[2];
};
