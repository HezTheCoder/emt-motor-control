/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

//ATTENTION! FILE IS NOT USED!

#include "LCD_DISCO_F429ZI.h"
#include "16key.h"

class UIViewController
{
    public:
        virtual void DisplayTick(LCD* pLcd, Control16KeyPanel* pKeypnl) = 0;
};