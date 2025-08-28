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


#define SAWTOOTH_PERIOD       5000000U  // Corresponds to the peak of the sawtooth
#define SAWTOOTH_INCREMENT    100000U      // Step size for the ramp
#define BLINK_COUNT_MAX       10        // 10 blinks (10 on + 10 off)

volatile uint16_t ledBlinkCount = 0;
__interrupt  void ecap2_isr(void); // 声明中断服务函数



//
// InitAPwm1 - Configure eCAP1 in APWM mode to generate a sawtooth wave
//
void InitAPwm1(void)
{
    EALLOW;
    ECap1Regs.ECCTL2.bit.CAP_APWM = 1;      // Enable APWM mode
    ECap1Regs.CAP1 = SAWTOOTH_PERIOD;       // Set Period value
    ECap1Regs.CAP2 = SAWTOOTH_INCREMENT;    // Set initial Compare value
    ECap1Regs.CAP4 = SAWTOOTH_INCREMENT;    // Set initial Shadow Compare value
    ECap1Regs.ECCLR.all = 0x0FF;            // Clear pending interrupts
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = 2;      // Syncout on period match
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start counter
    EDIS;
}

//
// InitECap2Capture - Configure eCAP2 in capture mode
//
void InitECap2Capture(void)
{
    EALLOW;
    ECap2Regs.ECCTL2.bit.CAP_APWM = 0;      // Disable APWM mode (Capture Mode)
    ECap2Regs.ECCTL2.bit.CONT_ONESHT = 0;   // Continuous capture mode
    ECap2Regs.ECCTL1.bit.CAP1POL = 0;       // Capture on Rising Edge
    ECap2Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset counter on capture event
    ECap2Regs.ECEINT.bit.CEVT1 = 1;         // Enable Capture Event 1 interrupt
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start counter
    EDIS;
}

void InitTestGpioAndXbar(void)
{
    EALLOW;
    // --- 输出配置 ---
    // 选择 eCAP1.OUT 作为 OUTPUTXBAR3 的 MUX0 输出
    OutputXbarRegs.EXT64_OUTPUT3MUX0TO15CFG.bit.MUX0 = 3; // Select ECAP1.OUT on Mux0
    OutputXbarRegs.EXT64_OUTPUT3MUXENABLE.bit.MUX0 = 1;  // Enable MUX0 for ECAP1.OUT
    // 将 GPIO5 配置为 OUTPUTXBAR3 的输出
    GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3; // GPIO5 = OUTPUTXBAR3

    // --- 输入配置 ---
    // 将 GPIO5 配置为 eCAP2 的输入
    InputXbarRegs.INPUT7SELECT = 5; // INPUT7 连接到 GPIO5 (eCAP2 的输入)
    EDIS;
}

// LED 闪烁中断服务程序
__interrupt  void ecap2_isr(void)
{
    // 闪烁10次
    if (ledBlinkCount < BLINK_COUNT_MAX) // 10次亮灭为20个状态
    {
        GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 0);// Turn on LED
        DELAY_US(5000);
        GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 1);// Turn off LED
        DELAY_US(5000);
        ledBlinkCount++;
    }

    // 清除 eCAP 中断标志位
    ECap2Regs.ECCLR.bit.CEVT1 = 1;
    ECap2Regs.ECCLR.all = 0x0FF;          // Clear pending __interrupts
    // 响应 PIE 中断
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

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
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    InitGpio();
    GPIO_SetupPinMux(DEVICE_GPIO_PIN_LED1, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_LED1, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(DEVICE_GPIO_PIN_LED2, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_LED2, GPIO_OUTPUT, GPIO_PUSHPULL);    

    InitAPwm1();
    InitECap2Capture();
    InitTestGpioAndXbar();
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

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.ECAP1_INT = &ecap2_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
    // Enable INT1 which is connected to WAKEINT:
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER4.bit.INTx2 = 1;          // Enable PIE Group 4 INT2 correspond ecap2 INT2

    IER |= M_INT4;                              // Enable CPU INT4
    EINT;                                       // Enable Global Interrupts

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;
    uint32_t current_compare = SAWTOOTH_INCREMENT;
    //
    // Loop Forever
    //
    for(;;)
    {
        GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 1);// Turn off LED
        GPIO_WritePin(DEVICE_GPIO_PIN_LED2, 1);// Turn off LED

        current_compare += SAWTOOTH_INCREMENT;
        // 模拟锯齿波上升
        // 通过逐渐增加比较值来提高占空比
        if(current_compare >= SAWTOOTH_PERIOD)
        {
            current_compare = SAWTOOTH_INCREMENT;
            GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 0);// Turn on LED
            DELAY_US(2000000);
        }
        //
        // Update the shadow register. The new compare value will be loaded
        // at the start of the next PWM period.
        //
        ECap1Regs.CAP4 = current_compare;
        DELAY_US(100000); // 延时以控制锯齿波的斜率


        // GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 0);// Turn on LED
        // GPIO_WritePin(DEVICE_GPIO_PIN_LED1, 1);// Turn off LED
        // DELAY_US(500000);
    }
}

//
// End of File
//
