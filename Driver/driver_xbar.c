#include "driver_xbar.h"

void sInitInputXbar(void);


void sInitInputXbar(void)
{
    EALLOW;
    InputXbarRegs.INPUT4SELECT = 32;    // xint1, gpio47, buckbst current overINPUT4

    InputXbarRegs.INPUT5SELECT = 41;    // xint2, gpio49, bus volt overINPUTS
    
    InputXbarRegs.INPUT7SELECT = 37;    // capl,  gpio39, grid zero M crossINPUT7
    InputXbarRegs.INPUT8SELECT = 36;    // cap2,  gpio46, inv current overINPUT8
    InputXbarRegs.INPUT9SELECT = 38;    // cap3,  gpio38, grid zero S crossINPUT9
    InputXbarRegs.INPUT10SELECT = 87;   // cap4,  gpio87, pv2 current overINPUT10
    InputXbarRegs.INPUT11SELECT = 86;   // cap5,  gpio86, pv1 current overINPUT11
    EDIS;
}


void sInitXBAR(void){
    sInitInputXbar();
}
//
// End of File
//
