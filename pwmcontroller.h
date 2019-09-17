/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#pragma once
#include "mbed.h"

enum MtrOperationMode
{
       MTR_OP_MODE_PWM,
       MTR_OP_MODE_ANALOG,
       MTR_OP_MODE_SHUTDOWN
};

class PWMController
{
    public:
    PWMController(PinName motorPwmModeControlPin, PinName motorLevelModeControlPin,
        MtrOperationMode initialOperationMode = MTR_OP_MODE_SHUTDOWN,
        float initialDutyCycle = 0.0f, float initialOperationPeriod = 0.0005f);
    
    //Set the operation duty cycle (in percent). Values above 1 get clamped to 1, values below
    //0 get clamped to 0. 0.0 turns off the motor.
    void SetDutyCycle(float dutyCycle = 1.0f);
    
    //Set the operation period (in seconds).
    void SetOperationPeriod(float period = 0.0005f);
    
    //Set the operation mode (Level or PWM). In Level operation mode, the duty cycle is interpreted
    //as a percentage of the maximum motor control output voltage.
    //void SetOperationMode(bool UseLevelMode);
    
    void SetOperationMode(MtrOperationMode OpMode);
    
    float GetCurrentDutyCycle();
    float GetCurrentOperationPeriod();
    MtrOperationMode GetCurrentOperationMode();
    
    protected:
    void EnforceOperationMode();
    
    PwmOut motorPwmDriver;
    AnalogOut motorLevelDriver;
    float curDutyCycle, onResumeDutyCycle, onResumeLevel, curOperationPeriod;
    MtrOperationMode curOperationMode;
};