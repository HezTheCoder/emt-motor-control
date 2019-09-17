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

class UIDriver
{
    public:
    UIDriver(LCD* PLcd, Control16KeyPanel* PKeypnl);
    void SetCurrentViewController(void (*)(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB));
    void StartViewControllerLoop(PWMController* PPwmController);
    
    private:
    void (*pCurViewController)(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB);
    bool viewControllerLoopIsActive;
    LCD* pLcd;
    Control16KeyPanel* pKeypnl;
};