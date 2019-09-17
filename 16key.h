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

#define COLUMN_STROBE_WAIT_TIME 0.0167f
#define COLUMN_SENSE_ENERGIZE_WAIT_TIME 0.00835f
//#define ROW_STROBE_WAIT_TIME 0.0167f

class Control16KeyPanel
{
    public:
    //The object must be created with the pins needed to sense the keys.
    Control16KeyPanel(PinName pinColumn0Strobe, PinName pinColumn1Strobe, PinName pinColumn2Strobe, 
        PinName pinColumn3Strobe, PinName pinRow0Sense, PinName pinRow1Sense, PinName pinRow2Sense,
        PinName pinRow3Sense);
        
    /*Control16KeyPanel(PinName pinColumn0Sense, PinName pinColumn1Sense, PinName pinColumn2Sense, 
        PinName pinColumn3Sense, PinName pinRow0Strobe, PinName pinRow1Strobe, PinName pinRow2Strobe,
        PinName pinRow3Strobe);
    */
        
    unsigned int ReadKeyPanelState();
    //pCharsOut must be buffer of 16 characters!
    void ReadKeyPanelStateBits(char* pCharsOut);
    void SetKeyDisableMask(unsigned int mask);
        
    private:
    unsigned int keyDisableMask;
    DigitalOut column0Strobe, column1Strobe, column2Strobe, column3Strobe;
    DigitalIn row0Sense, row1Sense, row2Sense, row3Sense;
    //DigitalIn column0Sense, column1Sense, column2Sense, column3Sense;
    //DigitalOut row0Strobe, row1Strobe, row2Strobe, row3Strobe;
};