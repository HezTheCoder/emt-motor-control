/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#include "pwmcontroller.h"

PWMController::PWMController(PinName motorPwmModeControlPin, PinName motorLevelModeControlPin, 
    MtrOperationMode InitialOperationMode, float initialDutyCycle, float initialOperationPeriod) : 
    motorPwmDriver(motorPwmModeControlPin),
    motorLevelDriver(motorLevelModeControlPin)
{
    curOperationMode = InitialOperationMode;    
    curDutyCycle = initialDutyCycle;
    curOperationPeriod = initialOperationPeriod;
    
    EnforceOperationMode();
}

void PWMController::EnforceOperationMode()
{
    switch(curOperationMode)
    {
        case MTR_OP_MODE_PWM:
            motorPwmDriver.write(curDutyCycle);
            motorLevelDriver.write(0.0f);
            break;
        case MTR_OP_MODE_ANALOG:
            motorPwmDriver.write(0.0f);
            motorPwmDriver.period(curOperationPeriod);
            motorLevelDriver.write(curDutyCycle);
            break;
        case MTR_OP_MODE_SHUTDOWN:
            motorPwmDriver.write(0.0f);
            motorLevelDriver.write(0.0f);   
    }   
}
    
void PWMController::SetDutyCycle(float dutyCycle)
{
    if(dutyCycle < 0.0f){ curDutyCycle = 0.0f; }
    else
    {
        if(dutyCycle > 1.0f){ curDutyCycle = 1.0f; }
        else
        {
            curDutyCycle = dutyCycle;   
        }
    }
    
    EnforceOperationMode();
}

void PWMController::SetOperationPeriod(float operationPeriod)
{
    //The system crashes if a period of 0 or less is entered, so we can't allow any inputs
    //<= 0.0f.
    if(operationPeriod <= 0.0f)
    {
        motorPwmDriver.period(0.0001f); 
        curOperationPeriod = 0.0001f;
    }
    else
    {
        curOperationPeriod = operationPeriod;
    }
    
    EnforceOperationMode();
}

void PWMController::SetOperationMode(MtrOperationMode OpMode)
{
    curOperationMode = OpMode;
    EnforceOperationMode();
}

float PWMController::GetCurrentDutyCycle(){ return curDutyCycle; }

float PWMController::GetCurrentOperationPeriod(){ return curOperationPeriod; }

MtrOperationMode PWMController::GetCurrentOperationMode(){ return curOperationMode; }