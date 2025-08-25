//#############################################################################
//
// FILE:   led_ex1_blinky.c
//
// TITLE:  LED Blinky Example
//
//! \addtogroup bitfield_example_list
//! <h1> LED Blinky Example </h1>
//!
//! This example demonstrates how to blink a LED.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
//
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"
#include "driver_boot.h"

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
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_BANK3_SECTOR0);
#else
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
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
