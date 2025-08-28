#include "f28p65x_device.h"
#include "f28p65x_xint.h"
#include "driver_xint.h"


void sInitXint1(void)
{
    XintRegs.XINT1CR.bit.POLARITY = 0;  // Falling edge interrupt
    XintRegs.XINT1CR.bit.ENABLE = 1;    // Enable XINT1
}

void sInitXint2(void)
{
    XintRegs.XINT2CR.bit.POLARITY = 0;  // Falling edge interrupt
    XintRegs.XINT2CR.bit.ENABLE = 1;    // Enable XINT2
}

void sInitXint(void)
{
    sInitXint1();
    sInitXint2();
}
//
// End of File
//
