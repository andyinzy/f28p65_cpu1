//#############################################################################
//
// File: driver_xbar.c
//
// Description: This file contains functions for configuring the Input Crossbar
//              (XBAR) module on the F28P65x device. It includes initialization
//              functions to map external signals to internal peripherals for
//              interrupt and capture functionality.
//
//#############################################################################

#include "driver_xbar.h"

// void sInitInputXbar(void);


// void sInitInputXbar(void)
// {
//     EALLOW;
//     InputXbarRegs.INPUT4SELECT = 32;    // xint1, gpio47, buckbst current overINPUT4

//     InputXbarRegs.INPUT5SELECT = 41;    // xint2, gpio49, bus volt overINPUTS
    
//     InputXbarRegs.INPUT7SELECT = 37;    // ecap1,  gpio39, grid zero M crossINPUT7
//     InputXbarRegs.INPUT8SELECT = 36;    // ecap2,  gpio46, inv current overINPUT8
//     InputXbarRegs.INPUT9SELECT = 38;    // ecap3,  gpio38, grid zero S crossINPUT9
//     InputXbarRegs.INPUT10SELECT = 87;   // ecap4,  gpio87, pv2 current overINPUT10
//     InputXbarRegs.INPUT11SELECT = 86;   // ecap5,  gpio86, pv1 current overINPUT11
//     EDIS;
// }


// void sInitXBAR(void){
//     sInitInputXbar();
// }
//
// End of File
//
