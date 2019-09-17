/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#include "ui.h"

UIDriver::UIDriver(LCD* PLcd, Control16KeyPanel* PKeypnl)
{
    pCurViewController = 0;
    viewControllerLoopIsActive = true;
    pLcd = PLcd;
    pKeypnl = PKeypnl;
}

void UIDriver::SetCurrentViewController(void (*PViewControllerFunc)(UIDriver*, LCD*, Control16KeyPanel*, PWMController*, void*, void*))
{
    //Clear lcd first
    pLcd->Clear(LCD_COLOR_WHITE);
    pCurViewController = PViewControllerFunc;
    
    wait(0.20f);
}

void UIDriver::StartViewControllerLoop(PWMController* PPwmController)
{
    while(viewControllerLoopIsActive)
    {
        pCurViewController(this, pLcd, pKeypnl, PPwmController, 0, 0);
    }
}