/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#include "mbed.h"
#include "LCD_DISCO_F429ZI.h"
#include "pwmcontroller.h"
#include "pwmcontrollerui.h"
#include "ui.h"

DigitalOut led1(LED1);

int main()
{      
    LCD lcd;
    Control16KeyPanel keypnl(PE_5, PE_4, PE_3, PE_2, PE_6, PC_13, PB_3, PB_4);
    UIDriver uiDrv(&lcd, &keypnl);
    PWMController pwmc(PC_8, PA_5);
    
    led1.write(1);
    
    uiDrv.SetCurrentViewController(PWMControllerUI::IdleScreen);
    
    uiDrv.StartViewControllerLoop(&pwmc);
}