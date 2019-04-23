#pragma once

#include "kinmatics.hpp"

#define gaitResolution          16
#define gaitXWidth              0.06
#define gaitYUp                 0.045
#define gaitYDown               0.07

typedef enum gait_e
{
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT,
    RESET,
    CLIMBING,

} gait_e;

legParam_t legParam = {

    0,    //actuator distance
    0.05, //length A1
    0.05, //length A2
    0.05, //length B1
    0.05  //lenght B2

};

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

#define gaitXWidthClimb              0.03
#define gaitYUpClimb                 0.05
#define gaitYDownClimb               0.07

//gaitX represents creep gait for forward / backward motion
float gaitXclimb[gaitResolution] =
    {
        -gaitXWidthClimb, //beat 0
        -gaitXWidthClimb,
        -gaitXWidthClimb + (gaitXWidthClimb * 2 / 3),
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 3),
        gaitXWidthClimb, //beat 1
        gaitXWidthClimb,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 1,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 2,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 3, //beat 2
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 4,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 5,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 6,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 7, //beat 3
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 8,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 9,
        gaitXWidthClimb - (gaitXWidthClimb * 2 / 11) * 10};

//gaitY represents creep gait for up / down motion
float gaitYclimb[16] =
    {
        gaitYDownClimb, //beat 0
        gaitYUpClimb,
        gaitYUpClimb,
        gaitYUpClimb,
        gaitYDownClimb, //beat 1
        gaitYDownClimb,
        gaitYDownClimb,
        gaitYDownClimb,
        gaitYDownClimb, //beat 2
        gaitYDownClimb,
        gaitYDownClimb,
        gaitYDownClimb,
        gaitYDownClimb, //beat 3
        gaitYDownClimb,
        gaitYDownClimb,
        gaitYDownClimb};