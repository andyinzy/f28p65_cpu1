//#############################################################################
//
// FILE:   main.c
// TITLE:  Migration Sanity Test: Manual GPIO Trigger for eCAP Capture/ISR
//
//#############################################################################

// GPIO0 is xint 1
// GPIO7 is ecap 1
// GPIO5 is ecap 2
// 


#include "f28x_project.h"
#include "driver_boot.h"
#include "driver_ecap.h"

//
// Defines for our simple test
//
#define LED_PIN         12  // GPIO12, connected to an LED
#define DEVICE_GPIO_PIN_LED2    13
#define TRIGGER_PIN     32  // GPIO32, will be toggled in software
#define CAPTURE_PIN     5   // GPIO5, will receive the signal from TRIGGER_PIN

#define BLINK_COUNT_MAX 20  // Blink 10 times then stop

//
// Globals
//
volatile uint16_t isr_exc_cnt = 0;

//
// Function Prototypes
//
void InitTestGpio(void);
void InitECap1(void);
void InitECap2(void);
void InitXbar(void);
void InitXintGpio(void);
__interrupt void ecap1_isr(void);
__interrupt void ecap2_isr(void);
__interrupt void xint1_isr(void);

//
// Main
//
void main(void)
{
    // 1. Initialize System
    InitSysCtrl();
    InitGpio();



    // 3. Initialize and configure Interrupts
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    // check pievecttable for xint1 (1.4) and ecap2 (4.2)
    EALLOW;
    PieVectTable.ECAP1_INT = &ecap1_isr;
    PieVectTable.ECAP2_INT = &ecap2_isr;
    PieVectTable.XINT1_INT = &xint1_isr;
    EDIS;

    // Enable the correct PIE channel for ECAP2_INT (Group 4, INT 2)
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER4.bit.INTx1 = 1;          // 4.1 ecap1 
    PieCtrlRegs.PIEIER4.bit.INTx2 = 1;          // 4.2 ecap2
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // 1.4 xint1

    // Enable the corresponding CPU interrupt (INT4 for PIE Group 4)
    IER |= M_INT1;
    IER |= M_INT4;

    // 2. Configure peripherals for our test
    sInitEcap();
    InitTestGpio();
    // InitECap1();
    // InitECap2();
    InitXbar();
    // Enable global interrupts
    EINT;
    ERTM;

    
    InitXintGpio();
    GPIO_SetupXINT1Gpio(0);
    XintRegs.XINT1CR.bit.POLARITY = 0;          // Falling edge interrupt
    XintRegs.XINT1CR.bit.ENABLE = 1;            // Enable XINT1


    // 4. Main loop: Manually toggle the trigger pin
    for(;;)
    {
        // Set trigger pin high
        GPIO_WritePin(TRIGGER_PIN, 1);

        // Delay to ensure the signal is stable
        DELAY_US(100000); // 100ms

        // Set trigger pin low
        GPIO_WritePin(TRIGGER_PIN, 0);

        // Delay
        DELAY_US(100000); // 100ms
    }
}

//
// InitTestGpio - Configure pins for the test
//
void InitTestGpio(void)
{
    // Configure LED_PIN (GPIO12) as a push-pull output
    GPIO_SetupPinMux(LED_PIN, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(LED_PIN, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(LED_PIN, 1); // Start with LED off

    // Configure DEVICE_GPIO_PIN_LED2 (GPIO13) as a push-pull output
    GPIO_SetupPinMux(DEVICE_GPIO_PIN_LED2, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(DEVICE_GPIO_PIN_LED2, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_WritePin(DEVICE_GPIO_PIN_LED2, 1); // Start with LED off

    // Configure TRIGGER_PIN (GPIO32) as a push-pull output
    GPIO_SetupPinMux(TRIGGER_PIN, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(TRIGGER_PIN, GPIO_OUTPUT, GPIO_PUSHPULL);


    // Configure ECAP2 on GPIO5
    // No pull-up needed as it's driven by TRIGGER_PIN
    // GPIO_SetupPinMux(CAPTURE_PIN, GPIO_MUX_CPU1, 0);
    // GPIO_SetupPinOptions(CAPTURE_PIN, GPIO_INPUT, GPIO_SYNC);


    /*GRID_ZERO_M,ecap1 */
    // GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0b00;
    // GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0b00;
    // GpioCtrlRegs.GPACSEL1.bit.GPIO5 = 0;/*cpu1*/
    // GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;/*input*/
    // // 不用qualified
    // // GpioCtrlRegs.GPBCTRL.bit.QUALPRDO=0x30;/*GPI032~GPI039*/
    // // GpioCtrlRegs.GPBQSEL1.bit.GPIO39 = 1;/*3 samples,2*2*48*5ns= 960ns*/
    // GpioCtrlRegs.GPAPUD.bit.GPIO5 =0;/*pullup*/
}


//
// InitECap1 - Configure eCAP1 for simple falling edge capture
//
void InitECap1(void)
{
    EALLOW;
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap1Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap1Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap1Regs.ECCTL1.bit.CAP1POL = 0;       // Falling Edge
    ECap1Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;   // Operate in continuous mode
    ECap1Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap1Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap1Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    EDIS;
}

//
// InitECap2 - Configure eCAP2 for simple rising edge capture
//
void InitECap2(void)
{
    EALLOW;
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Stop counter
    ECap2Regs.ECEINT.all = 0x0000;          // Disable all capture interrupt
    ECap2Regs.ECCLR.all = 0xFFFF;           // Clear all Ecap interrupt flag
    ECap2Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1 register loads
    ECap2Regs.ECCTL1.bit.CAP1POL = 1;       // Falling Edge
    ECap2Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset after event 1 has been captured
    ECap2Regs.ECCTL2.bit.CONT_ONESHT = 1;   // Operate in continuous mode
    ECap2Regs.ECCTL2.bit.STOP_WRAP = 0;     // Wrap after capture event 1
    ECap2Regs.ECEINT.bit.CEVT1 = 1;         // Enable capture event 1 interrupt
    ECap2Regs.ECCTL2.bit.REARM = 1;         // One-shot re-arm
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
    EDIS;
}

//
// InitXbar - Configure Input XBAR to route CAPTURE_PIN to eCAP2
//
void InitXbar(void)
{
    EALLOW;
    // eCAP1 on GPIO7
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pullup on GPIO7
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;  // Synch to SYSCLKOUT
    InputXbarRegs.INPUT7SELECT = 7;       // INPUT7 = GPIO7
    ECap1Regs.ECCTL0.bit.INPUTSEL = 7;    // Select eCAP1 TO INPUTXBAR8
    
    // eCAP2 on GPIO5
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pullup on GPIO5
    GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;  // Synch to SYSCLKOUT
    InputXbarRegs.INPUT8SELECT = 5; // INPUT8 = GPIO5
    ECap2Regs.ECCTL0.bit.INPUTSEL = 8;      // Select eCAP1 TO INPUTXBAR9
    EDIS;
}

//
// ecap1_isr - The Interrupt Service Routine
//
__interrupt void ecap1_isr(void)
{
    for(isr_exc_cnt = 0; isr_exc_cnt < BLINK_COUNT_MAX; isr_exc_cnt++)
    {
        // blink LED
        GPIO_WritePin(LED_PIN, 0);// Turn on
        DELAY_US(5000);
        GPIO_WritePin(LED_PIN, 1);// Turn off
        DELAY_US(5000);
    }

    // Clear eCAP interrupt flags
    ECap1Regs.ECCLR.bit.CEVT1 = 1;
    ECap1Regs.ECCLR.bit.INT = 1;

    // Acknowledge this interrupt to receive more interrupts from this PIE group
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

//
// ecap2_isr - The Interrupt Service Routine
//
__interrupt void ecap2_isr(void)
{
    for(isr_exc_cnt = 0; isr_exc_cnt < BLINK_COUNT_MAX; isr_exc_cnt++)
    {
        // blink LED
        GPIO_WritePin(LED_PIN, 0);// Turn on
        DELAY_US(5000);
        GPIO_WritePin(LED_PIN, 1);// Turn off
        DELAY_US(5000);
    }

    // Clear eCAP interrupt flags
    ECap2Regs.ECCLR.bit.CEVT1 = 1;
    ECap2Regs.ECCLR.bit.INT = 1;

    // Acknowledge this interrupt to receive more interrupts from this PIE group
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

__interrupt void xint1_isr(void)
{
    for(isr_exc_cnt = 0; isr_exc_cnt < BLINK_COUNT_MAX; isr_exc_cnt++)
    {
        // blink LED
        GPIO_WritePin(DEVICE_GPIO_PIN_LED2, 0);// Turn on
        DELAY_US(5000);
        GPIO_WritePin(DEVICE_GPIO_PIN_LED2, 1);// Turn off
        DELAY_US(5000);
    }

    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


void InitXintGpio(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;          // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        // XINT1 Synch to SYSCLKOUT only
    EDIS;
}
//
// End of file
//
