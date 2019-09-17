/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#include "16key.h"

Control16KeyPanel::Control16KeyPanel(PinName pinColumn0Strobe, PinName pinColumn1Strobe, 
        PinName pinColumn2Strobe, PinName pinColumn3Strobe, PinName pinRow0Sense, PinName pinRow1Sense, 
        PinName pinRow2Sense, PinName pinRow3Sense) : 
        column0Strobe(pinColumn0Strobe),
        column1Strobe(pinColumn1Strobe),
        column2Strobe(pinColumn2Strobe),
        column3Strobe(pinColumn3Strobe),
        row0Sense(pinRow0Sense, PullDown),
        row1Sense(pinRow1Sense, PullDown),
        row2Sense(pinRow2Sense, PullDown),
        row3Sense(pinRow3Sense, PullDown)
{
    keyDisableMask = 0;
    
    column0Strobe = 0;
    column1Strobe = 0;
    column2Strobe = 0;
    column3Strobe = 0;
}

/*
Control16KeyPanel::Control16KeyPanel(PinName pinColumn0Sense, PinName pinColumn1Sense, PinName pinColumn2Sense, 
        PinName pinColumn3Sense, PinName pinRow0Strobe, PinName pinRow1Strobe, PinName pinRow2Strobe,
        PinName pinRow3Strobe) : 
        column0Sense(pinColumn0Sense),
        column1Sense(pinColumn1Sense),
        column2Sense(pinColumn2Sense),
        column3Sense(pinColumn3Sense),
        row0Strobe(pinRow0Strobe),
        row1Strobe(pinRow1Strobe),
        row2Strobe(pinRow2Strobe),
        row3Strobe(pinRow3Strobe)
{
       keyDisableMask = 0;
       
       row0Strobe = 0;
       row1Strobe = 0;
       row2Strobe = 0;
       row3Strobe = 0;
}
*/

unsigned int Control16KeyPanel::ReadKeyPanelState()
{
    unsigned int readButtons = 0;
    
    //Power column 0
    column0Strobe = 1;
    wait(COLUMN_SENSE_ENERGIZE_WAIT_TIME); //wait for the line to energize
    readButtons |= row0Sense.read() | (row1Sense.read() << 4) | (row2Sense.read() << 8) | (row3Sense.read() << 12);
    column0Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 1
    column1Strobe = 1;
    wait(COLUMN_SENSE_ENERGIZE_WAIT_TIME);
    readButtons |= (row0Sense.read() << 1) | (row1Sense.read() << 5) | (row2Sense.read() << 9) | (row3Sense.read() << 13);
    column1Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 2
    column2Strobe = 1;
    wait(COLUMN_SENSE_ENERGIZE_WAIT_TIME);
    readButtons |= (row0Sense.read() << 2) | (row1Sense.read() << 6) | (row2Sense.read() << 10) | (row3Sense.read() << 14);
    column2Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 3
    column3Strobe = 1;
    wait(COLUMN_SENSE_ENERGIZE_WAIT_TIME);
    readButtons |= (row0Sense.read() << 3) | (row1Sense.read() << 7) | (row2Sense.read() << 11) | (row3Sense.read() << 15);
    column3Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    /*
    //Power row 0
    row0Strobe = 1;
    readButtons |= (column0Sense.read() ? 1 : 0) | (column1Sense.read() ? 1 << 1 : 0) | (column2Sense.read() ? 1 << 2 : 0) | (column3Sense.read() ? 1 << 3 : 0);
    row0Strobe = 0;
    wait(ROW_STROBE_WAIT_TIME);
    
    //Power row 1
    row1Strobe = 1;
    readButtons |= (column0Sense.read() << 4) | (column1Sense.read() << 5) | (column2Sense.read() << 6) | (column3Sense.read() << 7);
    row1Strobe = 0;
    wait(ROW_STROBE_WAIT_TIME);
    
    //Power row 2
    row2Strobe = 1;
    readButtons |= (column0Sense.read() << 8) | (column1Sense.read() << 9) | (column2Sense.read() << 10) | (column3Sense.read() << 11);
    row2Strobe = 0;
    wait(ROW_STROBE_WAIT_TIME);
    
    //Power row 3
    row3Strobe = 1;
    readButtons |= (column0Sense.read() << 12) | (column1Sense.read() << 13) | (column2Sense.read() << 14) | (column3Sense.read() << 15);
    row3Strobe = 0;
    wait(ROW_STROBE_WAIT_TIME);
    */
    
    //HACK: There is currently a hardware issue forcing buttons 0-11 to 1. We will suppress the
    //buttons manually and hopefully we'll find a fix soon.
    //UPDATE: Testing removing the hack
    return readButtons;
}

void Control16KeyPanel::ReadKeyPanelStateBits(char* pCharsOut)
{
    unsigned int readButtons = ReadKeyPanelState();
    
    pCharsOut[0] = (readButtons & 0x0001 ? '1' : '0');
    pCharsOut[1] = (readButtons & 0x0002 ? '1' : '0');
    pCharsOut[2] = (readButtons & 0x0004 ? '1' : '0');
    pCharsOut[3] = (readButtons & 0x0008 ? '1' : '0');

    pCharsOut[4] = (readButtons & 0x0010 ? '1' : '0');
    pCharsOut[5] = (readButtons & 0x0020 ? '1' : '0');
    pCharsOut[6] = (readButtons & 0x0040 ? '1' : '0');
    pCharsOut[7] = (readButtons & 0x0080 ? '1' : '0');
    
    pCharsOut[8] = (readButtons & 0x0100 ? '1' : '0');
    pCharsOut[9] = (readButtons & 0x0200 ? '1' : '0');
    pCharsOut[10] = (readButtons & 0x0400 ? '1' : '0');
    pCharsOut[11] = (readButtons & 0x0800 ? '1' : '0');
    
    pCharsOut[12] = (readButtons & 0x1000 ? '1' : '0');
    pCharsOut[13] = (readButtons & 0x2000 ? '1' : '0');
    pCharsOut[14] = (readButtons & 0x4000 ? '1' : '0');
    pCharsOut[15] = (readButtons & 0x8000 ? '1' : '0');
    
    //Power column 0
    /*
    column0Strobe = 1;
    pCharsOut[0] = (row0Sense.read() == 1 ? '1' : '0');
    pCharsOut[4] = (row1Sense.read() == 1 ? '1' : '0');
    pCharsOut[8] = (row2Sense.read() == 1 ? '1' : '0');
    pCharsOut[12] = (row3Sense.read() == 1 ? '1' : '0');
    column0Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 1
    column1Strobe = 1;
    pCharsOut[1] = (row0Sense.read() == 1 ? '1' : '0');
    pCharsOut[5] = (row1Sense.read() == 1 ? '1' : '0');
    pCharsOut[9] = (row2Sense.read() == 1 ? '1' : '0');
    pCharsOut[13] = (row3Sense.read() == 1 ? '1' : '0');
    column1Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 2
    column2Strobe = 1;
    pCharsOut[2] = (row0Sense.read() == 1 ? '1' : '0');
    pCharsOut[6] = (row1Sense.read() == 1 ? '1' : '0');
    pCharsOut[10] = (row2Sense.read() == 1 ? '1' : '0');
    pCharsOut[14] = (row3Sense.read() == 1 ? '1' : '0');
    column2Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    
    //Power column 3
    column3Strobe = 1;
    pCharsOut[3] = (row0Sense.read() == 1 ? '1' : '0');
    pCharsOut[7] = (row1Sense.read() == 1 ? '1' : '0');
    pCharsOut[11] = (row2Sense.read() == 1 ? '1' : '0');
    pCharsOut[15] = (row3Sense.read() == 1 ? '1' : '0');
    column3Strobe = 0;
    wait(COLUMN_STROBE_WAIT_TIME);
    */
    
    //return (readButtons & ~keyDisableMask);    
}

void Control16KeyPanel::SetKeyDisableMask(unsigned int mask)
{
    keyDisableMask = mask;
}