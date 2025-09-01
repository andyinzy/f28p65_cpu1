//#############################################################################
//
// File: driver_ecap.c
//
// Description: This file contains functions for configuring and initializing
//              the Enhanced Capture (eCAP) modules on the F28P65x device.
//              It includes initialization functions for eCAP1 through eCAP5,
//              and an interrupt handler for eCAP1.
//
//#############################################################################

#include "f28p65x_device.h"
#include "f28p65x_ecap.h"
#include "driver_ecap.h"

// Global variables for ECAP capture counting
// volatile uint32_t gEcap1CaptureCount = 0;
// volatile uint32_t gEcap1LastCapture = 0;
// volatile uint16_t gEcapLedState = 0;

// ECAP1 interrupt handler function
void ECAP1_ISR_Handler(void)
{
    // // Increment ECAP1 capture count
    // gEcap1CaptureCount++;
    // gEcap1LastCapture = ECap1Regs.CAP1;  // Save captured value

    // // Toggle LED state to indicate capture occurred
    // sToggleEcapLed();

    // // Clear interrupt flags
    // ECap1Regs.ECCLR.bit.CEVT1 = 1;
    // ECap1Regs.ECCLR.bit.INT = 1;

    // // Acknowledge interrupt
    // PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

void sInitEcap1(void){
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap1Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap1Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap1Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Operate in continuous mode
    ECap1Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap1Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap1Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
}

void sInitEcap2(void){
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap2Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap2Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap2Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap2Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap2Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap2Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Operate in continuous mode
    ECap2Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap2Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap2Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
}

void sInitEcap3(void){
    ECap3Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap3Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap3Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap3Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap3Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap3Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap3Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Operate in continuous mode
    ECap3Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap3Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap3Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
}

void sInitEcap4(void){
    ECap4Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap4Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap4Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap4Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap4Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap4Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap4Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Operate in continuous mode
    ECap4Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap4Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap4Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
}

void sInitEcap5(void){
    ECap5Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap5Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap5Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap5Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap5Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap5Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap5Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Operate in continuous mode
    ECap5Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap5Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap5Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap5Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
}


//*****************************************************************************
//
// sInitEcap() 
//
//*****************************************************************************
void sInitEcap(void)
{
    sInitEcap1();
    sInitEcap2();
    sInitEcap3();
    sInitEcap4();
    sInitEcap5();
}
//
// End of File
//
