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

#include "LCD_DISCO_F429ZI.h"
#include "16key.h"
#include "pwmcontroller.h"
#include "ui.h"

namespace PWMControllerUI
{
    void IdleScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    //ParamA is interpreted as a void (void*) function.
    //ParamB is sent to that function.
    void UserWaitScreenSync(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void PerformKeypanelTest(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    //Prints out the current operation status of the motor.
    void MotorStatusScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void MotorDutyCycleSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void MotorPeriodSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void MotorDriveModeSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void MotorConfigurationScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    
    void SystemInformationScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
}