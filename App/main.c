//#############################################################################
//
// FILE:   main.c
//
// TITLE:  
//
//! \addtogroup bitfield_example_list
//! <h1>    </h1>
//!
//! This example demonstrates ...
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Defines
//
#define DEVICE_GPIO_PIN_LED1    12
#define DEVICE_GPIO_PIN_LED2    13

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Write the controller select setting into the appropriate field.
    //
    EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS4 = 1U;
    EDIS;

    DevCfgRegs.BANKMUXSEL.bit.BANK3 = 3U;
    DevCfgRegs.BANKMUXSEL.bit.BANK4 = 3U;

    //
    // Boot CPU2 core
    //
#ifdef _STANDALONE
#ifdef _FLASH
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

    //
    // Wait for IPC flag from CPU2
    //
	
    //IPCLtoRFlagSet(IPC_FLAG0);

    // while(IPCRtoLFlagBusy(IPC_FLAG0) == 0);
    // IPCRtoLFlagAcknowledge(IPC_FLAG0);

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    InitGpio();
    GPIO_SetupPinMux(DEVICE_GPIO_PIN_LED1, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_LED1, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(DEVICE_GPIO_PIN_LED2, GPIO_MUX_CPU2, 0);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_LED2, GPIO_OUTPUT, GPIO_PUSHPULL);    

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Turn on LED
        //
        GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 0);

        //
        // Delay for a bit.
        //
        DELAY_US(500000);

        //
        // Turn off LED
        //
        GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 1);

        //
        // Delay for a bit.
        //
        DELAY_US(500000);
    }
}

//
// End of File
//
