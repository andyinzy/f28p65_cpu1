//#############################################################################
//
// File: driver_boot.c
//
// Description: This file contains functions for booting CPU2 from CPU1.
//              It includes functions to check CPU2 reset status, boot CPU2
//              with specified boot mode, and control CPU2 reset.
//
//#############################################################################

#include "f28x_project.h"
#include "driver_boot.h"
#include "f28p65x_ipc_defines.h"

//*****************************************************************************
//
// SysCtl_isCPU2Reset()
//
//*****************************************************************************

bool SysCtl_isCPU2Reset(void)
{
    return(((*((volatile uint16_t *)(DEVCFG_BASE + SYSCTL_O_RSTSTAT))) &
            SYSCTL_RSTSTAT_CPU2RES) == 0U);
}

//*****************************************************************************
//
// Device_bootCPU2()
//
//*****************************************************************************
void Device_bootCPU2(uint32_t bootmode)
{
    // Configure the CPU1TOCPU2IPCBOOTMODE register
    // IPC_CPU1_L_CPU2_R
    Cpu1toCpu2IpcRegs.CPU1TOCPU2IPCBOOTMODE = (BOOT_KEY | bootmode);
    // Set IPC Flag 0
    IPCLtoRFlagSet(IPC_FLAG0);
    // Bring CPU2 out of reset. Wait for CPU2 to go out of reset.
    SysCtl_controlCPU2Reset();
    while(SysCtl_isCPU2Reset() == 0x1U);
}


//*****************************************************************************
//
// SysCtl_controlCPU2Reset()
//
//*****************************************************************************
void SysCtl_controlCPU2Reset(void)
{
    uint32_t clearvalue;
    uint32_t CPU2RESCTL_OFFSET = DEVCFG_BASE + SYSCTL_O_CPU2RESCTL;
    //Based on whether the Core is to be reset or not, the core would be put into reset or brought out.
    EALLOW;
    // Simplified to SYSCTL_CORE_ACTIVE status by default. write to the reset bits would be successful
    clearvalue = (*((volatile uint32_t *)(CPU2RESCTL_OFFSET)));
    clearvalue &= ~SYSCTL_CPU2RESCTL_RESET;
    (*((volatile uint32_t *)(CPU2RESCTL_OFFSET))) = (SYSCTL_REG_KEY &
                                                SYSCTL_CPU2RESCTL_KEY_M) |
                                                clearvalue;
    EDIS;
}

//
// End of File
//
