//*****************************************************************************
//
// Macros related to booting CPU2. These can be used while invoking the
// function Device_bootCPU2()
//
//*****************************************************************************

#ifndef DRIVER_BOOT_H
#define DRIVER_BOOT_H


#ifdef CPU1
#define BOOT_KEY                                        0x5A000000UL

#define BOOTMODE_BOOT_TO_FLASH_BANK0_SECTOR0            0x03U
#define BOOTMODE_BOOT_TO_FLASH_BANK0_SECTOR127_END      0x23U
#define BOOTMODE_BOOT_TO_FLASH_BANK1_SECTOR0            0x43U
#define BOOTMODE_BOOT_TO_FLASH_BANK2_SECTOR0            0x63U
#define BOOTMODE_BOOT_TO_FLASH_BANK3_SECTOR0            0x83U
#define BOOTMODE_BOOT_TO_FLASH_BANK4_SECTOR0            0xA3U
#define BOOTMODE_BOOT_TO_FLASH_BANK4_SECTOR127_END      0xC3U
#define BOOTMODE_BOOT_TO_SECURE_FLASH_BANK0_SECTOR0     0x0AU
#define BOOTMODE_BOOT_TO_SECURE_FLASH_BANK1_SECTOR0     0x4AU
#define BOOTMODE_BOOT_TO_SECURE_FLASH_BANK2_SECTOR0     0x6AU
#define BOOTMODE_BOOT_TO_SECURE_FLASH_BANK3_SECTOR0     0x8AU
#define BOOTMODE_BOOT_TO_SECURE_FLASH_BANK4_SECTOR0     0xAAU
#define BOOTMODE_IPC_MSGRAM_COPY_BOOT_TO_M1RAM          0x01U
#define BOOTMODE_BOOT_TO_M0RAM                          0x05U
#define BOOTMODE_BOOT_TO_FWU_FLASH                      0x0BU
#define BOOTMODE_BOOT_TO_FWU_FLASH_ALT1                 0x2BU
#define BOOTMODE_BOOT_TO_FWU_FLASH_ALT2                 0x4BU
#define BOOTMODE_BOOT_TO_FWU_FLASH_ALT3                 0x6BU

#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_100W            0x10000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_200W            0x20000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_300W            0x30000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_400W            0x40000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_500W            0x50000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_600W            0x60000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_700W            0x70000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_800W            0x80000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_900W            0x90000U
#define BOOTMODE_IPC_MSGRAM_COPY_LENGTH_1000W           0xA0000U
#endif


#define DEVCFG_BASE                     0x0005D000U
#define SYSCTL_O_RSTSTAT                0x13EU   // Reset Status register for secondary C28x CPUs
#define SYSCTL_O_CPU2RESCTL             0x13CU   // CPU2 Reset Control Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the RSTSTAT register
//
//*************************************************************************************************
#define SYSCTL_RSTSTAT_CPU2RES          0x1U   // CPU2 Reset Status bit
#define SYSCTL_RSTSTAT_CPU2NMIWDRST     0x2U   // Indicates whether a CPU2.NMIWD reset was issued to CPU2


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2RESCTL register
//
//*************************************************************************************************
#define SYSCTL_CPU2RESCTL_RESET         0x1U          // CPU2 Reset Control bit
#define SYSCTL_CPU2RESCTL_KEY_S         16U
#define SYSCTL_CPU2RESCTL_KEY_M         0xFFFF0000U   // Key Qualifier for writes to this register

//
//Keys for the System control registers write protection
//
#define SYSCTL_REG_KEY                  0xA5A50000U
#define SYSCTL_PLL_KEY                  0XCAFE0000U


bool SysCtl_isCPU2Reset(void);
void Device_bootCPU2(uint32_t);
void SysCtl_controlCPU2Reset(void);

#endif

//
// End of File
//
