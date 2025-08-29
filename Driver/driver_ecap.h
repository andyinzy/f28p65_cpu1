//#############################################################################
//
// File: driver_ecap.h
//
// Description: This header file contains definitions and declarations for the
//              Enhanced Capture (eCAP) module driver. It includes pin definitions,
//              edge detection constants, and function prototypes for eCAP
//              configuration and operation.
//
//#############################################################################

#ifndef DRIVER_ECAP_H
#define DRIVER_ECAP_H

#include "f28p65x_device.h"
#include "f28p65x_ecap.h"
#include "f28p65x_pie_defines.h"
#include "f28p65x_gpio_defines.h"
#include "f28p65x_gpio.h"

// ECAP test pin definitions
#define ECAP_TEST_PIN    31    // GPIO31 configured as ECAP1 input test pin
#define ECAP_LED_PIN     14    // GPIO14 configured as ECAP status LED pin

// ECAP edge detection definitions
#define EC_RISING  0
#define EC_FALLING 1

// // Global variables for ECAP capture counting
// extern volatile uint32_t gEcap1CaptureCount;
// extern volatile uint32_t gEcap1LastCapture;
// extern volatile uint16_t gEcapLedState;

// // Function declarations
extern void sInitEcap(void);
// extern void sInitEcapForTest(void);
// extern void sConfigEcap1(uint16_t polarity);
// extern void sSetupEcapTestPin(void);
// extern void sSetupEcapLedPin(void);
// extern uint32_t sGetEcap1CaptureCount(void);
// extern uint32_t sGetEcap1LastCapture(void);
// extern void sResetEcapCounters(void);
// extern void sToggleEcapLed(void);
// extern void ECAP1_ISR_Handler(void);

// // ????
// #define GET_CAP_GRID_ZERO_CNT()                 ECap1Regs.CAP1
// #define GET_CAP_GRID_ZERO_CNT_OVER_FLG()        ECap1Regs.ECFLG.bit.CTROVF
// #define GET_CAP_GRID_ZERO_CNT_S()               ECap3Regs.CAP1
// #define GET_CAP_GRID_ZERO_CNT_OVER_FLG_S()        ECap3Regs.ECFLG.bit.CTROVF

#endif
//
// End of File
//
