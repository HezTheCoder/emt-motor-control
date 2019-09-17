/************************************************************************************************

Programmable Motor Controller

Copyright (c) 2018 EMT2410 MCU PMC Team
(Hezron Castaneros, Nahshon Outten, Francisco Miranda)

This source code is licensed under the terms of the Creative Commons BY-NC-SA 
(Attribution-NonCommercial-ShareAlike) license version 3.0. See. Do not remove this notice.

This code is intended for educational/reference purposes only. 
Catch your own fish - Please don't plagiarize.

************************************************************************************************/

#include "pwmcontrollerui.h"
#include "mbed.h"

void PWMControllerUI::IdleScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    BSP_LCD_SetFont(&Font20);
    unsigned int keypnlState;
    
    while(1)
    {
        PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"MTRController", LEFT_MODE);
        PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)"[1]+[3] Keytest", LEFT_MODE);
        PLcd->DisplayStringAt(0, LINE(4), (uint8_t*)"[2]+[4] Log on", LEFT_MODE);
        
        //Need the key combination 1+3 to go to motor status screen.
        switch(PKeypnl->ReadKeyPanelState())
        {
            //Key combo 1+3 goes to keypad test.
            case 0x05:
                PUIDriver->SetCurrentViewController(PWMControllerUI::PerformKeypanelTest);
                return;
            case 0x0A:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorStatusScreen);
                return;
            
            //Key combo 2+4 goes to log-on.   
        }
        
        PLcd->DisplayStringAt(0, LINE(9), (uint8_t*)"Version 3.01", LEFT_MODE);
    }
}

void UserWaitScreenSync(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    PLcd->DisplayStringAt(0, LINE(7), (uint8_t*)"Please wait...", LEFT_MODE);
    ((void (*)(void*))ParamA)(ParamB);
    wait(1.00f);
}

void PWMControllerUI::PerformKeypanelTest(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    BSP_LCD_SetFont(&Font20);
    char pKeypnlStateBits[17];
    
    pKeypnlStateBits[16] = '\0';
    
    PLcd->DisplayStringAt(0, LINE(2), (uint8_t*)"Push some buttons", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)"[2]+[4] EXIT", LEFT_MODE);
    while(1)
    {
        PKeypnl->ReadKeyPanelStateBits(pKeypnlStateBits);
        PLcd->DisplayStringAt(0, LINE(5), (uint8_t*)pKeypnlStateBits, LEFT_MODE);

        if(PKeypnl->ReadKeyPanelState() == 0x0A)
        {
            PUIDriver->SetCurrentViewController(PWMControllerUI::IdleScreen);
            return;
        }
    }   
}

void PWMControllerUI::MotorStatusScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    char levelString[10];
    
    PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"** MTR STATUS **", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)"DRIVE MODE", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(6), (uint8_t*)"DUTY CYCLE/LEVEL", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(9), (uint8_t*)"OPER PERIOD", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(12), (uint8_t*)"[1] Set drive mode", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(13), (uint8_t*)"[2] Set duty cycle", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(14), (uint8_t*)"[3] Set period", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(15), (uint8_t*)"[4] BACK", LEFT_MODE);
    
    while(1)
    {
        switch(PPwmController->GetCurrentOperationMode())
        {
            case MTR_OP_MODE_SHUTDOWN:
                PLcd->DisplayStringAt(0, LINE(4), (uint8_t*)"MTR IS SHUTDOWN", LEFT_MODE);
                break;
            case MTR_OP_MODE_PWM:
                PLcd->DisplayStringAt(0, LINE(4), (uint8_t*)"PWM", LEFT_MODE);
                break;
            case MTR_OP_MODE_ANALOG:
                PLcd->DisplayStringAt(0, LINE(4), (uint8_t*)"Analog", LEFT_MODE);    \
                break;        
        }
        
        snprintf(levelString, 10, "%f", PPwmController->GetCurrentDutyCycle());
        PLcd->DisplayStringAt(0, LINE(7), (uint8_t*)levelString, LEFT_MODE);
        
        if(PPwmController->GetCurrentOperationMode())
        {
            PLcd->DisplayStringAt(0, LINE(10), (uint8_t*)"N/A", LEFT_MODE);
        }
        else
        {
            snprintf(levelString, 10, "%f", PPwmController->GetCurrentOperationPeriod());
            PLcd->DisplayStringAt(0, LINE(10), (uint8_t*)levelString, LEFT_MODE);
        }
        
        //Check for key presses
        switch(PKeypnl->ReadKeyPanelState())
        {
            case 0x01:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorDriveModeSelector);
                return;
            case 0x02:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorDutyCycleSelector);
                return;
            case 0x04:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorPeriodSelector);
                return;
            case 0x08:
                PUIDriver->SetCurrentViewController(PWMControllerUI::IdleScreen);
                return;   
        }
    }
}

void PWMControllerUI::MotorDriveModeSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"DRV MODE SELECT", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(6), (uint8_t*)"[1] SHUTDOWN", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(7), (uint8_t*)"[2] PWM", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(8), (uint8_t*)"[3] Analog", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(9), (uint8_t*)"[4] BACK", LEFT_MODE);
    
    while(1)
    {
        PLcd->ClearStringLine(LINE(2));
        
        switch(PPwmController->GetCurrentOperationMode())
        {
            case MTR_OP_MODE_SHUTDOWN:
                PLcd->DisplayStringAt(0, LINE(2), (uint8_t*)"SHUTDOWN", LEFT_MODE);
                break;
            case MTR_OP_MODE_PWM:
                PLcd->DisplayStringAt(0, LINE(2), (uint8_t*)"PWM     ", LEFT_MODE);
                break;
            case MTR_OP_MODE_ANALOG:
                PLcd->DisplayStringAt(0, LINE(2), (uint8_t*)"Analog  ", LEFT_MODE);
                break;
        }
        
        //Check for key presses
        switch(PKeypnl->ReadKeyPanelState())
        {
            case 0x01:
                PPwmController->SetOperationMode(MTR_OP_MODE_SHUTDOWN);
                break;
            case 0x02:
                PPwmController->SetOperationMode(MTR_OP_MODE_PWM);
                break;
            case 0x04:
                PPwmController->SetOperationMode(MTR_OP_MODE_ANALOG);
                break;
            case 0x08:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorStatusScreen);
                return;
        }
    }
}

void PWMControllerUI::MotorDutyCycleSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    char levelString[10];
    PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"CHANGE DUTY CYCLE", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(5), (uint8_t*)"[1] -0.01", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(6), (uint8_t*)"[2] +0.01", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(7), (uint8_t*)"[3] -0.001", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(8), (uint8_t*)"[4] +0.001", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(9), (uint8_t*)"[1+2] Zero", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(10), (uint8_t*)"[2+3] Maximum", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(11), (uint8_t*)"[3+4] Back", LEFT_MODE);     
    
    while(1)
    {
        snprintf(levelString, 10, "%f", PPwmController->GetCurrentDutyCycle());
        PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)levelString, LEFT_MODE);
        
        //Check for key presses
        switch(PKeypnl->ReadKeyPanelState())
        {
            case 0x01:
                PPwmController->SetDutyCycle(PPwmController->GetCurrentDutyCycle() - 0.01f);
                wait(0.10f);
                break;
            case 0x02:
                PPwmController->SetDutyCycle(PPwmController->GetCurrentDutyCycle() + 0.01f);
                wait(0.10f);
                break;
            case 0x04:
                PPwmController->SetDutyCycle(PPwmController->GetCurrentDutyCycle() - 0.001f);
                wait(0.10f);
                break;
            case 0x08:
                PPwmController->SetDutyCycle(PPwmController->GetCurrentDutyCycle() + 0.001f);
                wait(0.10f);
                break;
            case 0x03:
                PPwmController->SetDutyCycle(0.0f);
                wait(0.10f);
                break;
            case 0x06:
                PPwmController->SetDutyCycle(1.0f);
                wait(0.10f);
                break;
            case 0x0C:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorStatusScreen);
                return;
        }
    }
}

void PWMControllerUI::MotorPeriodSelector(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    char levelString[10];
    PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"CHANGE OP PERIOD", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(5), (uint8_t*)"[1] -0.01", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(6), (uint8_t*)"[2] +0.01", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(7), (uint8_t*)"[3] -0.001", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(8), (uint8_t*)"[4] +0.001", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(9), (uint8_t*)"[1+2] 1kHz", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(10), (uint8_t*)"[2+3] 5kHz", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(11), (uint8_t*)"[3+4] Back", LEFT_MODE); 
    
    while(1)
    {
        snprintf(levelString, 10, "%f", PPwmController->GetCurrentOperationPeriod());
        PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)levelString, LEFT_MODE);
        
        //Check for key presses
        switch(PKeypnl->ReadKeyPanelState())
        {
            case 0x01:
                PPwmController->SetOperationPeriod(PPwmController->GetCurrentOperationPeriod() - 0.01f);
                wait(0.10f);
                break;
            case 0x02:
                PPwmController->SetOperationPeriod(PPwmController->GetCurrentOperationPeriod() + 0.01f);
                wait(0.10f);
                break;
            case 0x04:
                PPwmController->SetOperationPeriod(PPwmController->GetCurrentOperationPeriod() - 0.001f);
                wait(0.10f);
                break;
            case 0x08:
                PPwmController->SetOperationPeriod(PPwmController->GetCurrentOperationPeriod() + 0.001f);
                wait(0.10f);
                break;
            case 0x03:
                PPwmController->SetOperationPeriod(0.001f);
                wait(0.10f);
                break;
            case 0x06:
                PPwmController->SetOperationPeriod(0.0002f);
                wait(0.10f);
                break;
            case 0x0C:
                PUIDriver->SetCurrentViewController(PWMControllerUI::MotorStatusScreen);
                return;
        }
    }
}

void PWMControllerUI::MotorConfigurationScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    PLcd->DisplayStringAt(0, LINE(1), (uint8_t*)"NOT AVAILABLE", LEFT_MODE);
}

void PWMControllerUI::SystemInformationScreen(UIDriver* PUIDriver, LCD* PLcd, Control16KeyPanel* PKeypnl, PWMController* PPwmController, void* ParamA, void* ParamB)
{
    PLcd->DisplayStringAt(0, LINE(2), (uint8_t*)"PWMController", LEFT_MODE);
    PLcd->DisplayStringAt(0, LINE(3), (uint8_t*)"v1.1", LEFT_MODE);
    
    PLcd->DisplayStringAt(0, LINE(5), (uint8_t*)"[16] Go back", LEFT_MODE);
}