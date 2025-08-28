#ifndef DRIVER_XBARS_H_
#define DRIVER_XBARS_H_

#include "f28p65x_device.h"
#include "f28p65x_epwm_xbar.h"
#include "f28p65x_xbar.h"

extern void sInitXBAR(void);

#define mGetXbarCmpss1TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS1_CTRIPH }
#define mGetXbarCmpss2TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS2_CTRIPH }
#define mGetXbarCmpss3TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS3_CTRIPH }
#define mGetXbarCmpss4TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS4_CTRIPH }
#define mGetXbarCmpss5TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS5_CTRIPH }
#define mGetXbarCmpss6TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS6_CTRIPH }
#define mGetXbarCmpss7TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS7_CTRIPH }
#define mGetXbarCmpss8TripHStat()  { XbarRegs.XBARFLG1.bit.CMPSS8_CTRIPH }


#define mHwBuckBoostCurrDischarHighStat()   XbarRegs.XBARFLG1.bit.CMPSS1_CTRIPH
#define mHwBuckBoostCurrCharHighStat()      XbarRegs.XBARFLG1.bit.CMPSS1_CTRIPL

#define mHwMidbusVoltHighStat()             XbarRegs.XBARFLG1.bit.CMPSS2_CTRIPH
#define mHwInverCurrPosHighStat()           XbarRegs.XBARFLG1.bit.CMPSS3_CTRIPH
#define mHwInverCurrNegHighStat()           XbarRegs.XBARFLG1.bit.CMPSS3_CTRIPL

#define mHwBusVoltHighStat()                XbarRegs.XBARFLG1.bit.CMPSS4_CTRIPH
#define mHwDabLvCurrDisCharHighStat()       XbarRegs.XBARFLG1.bit.CMPSS5_CTRIPH
#define mHwDabLvCurrCharHighStat()          XbarRegs.XBARFLG1.bit.CMPSS5_CTRIPL

#define mHwDabHvCurrDisCharHighStat()       XbarRegs.XBARFLG1.bit.CMPSS6_CTRIPH
#define mHwDabHvCurrCharHighStat()          XbarRegs.XBARFLG1.bit.CMPSS6_CTRIPL

#define mHwPv1CurrHighStat()                XbarRegs.XBARFLG1.bit.CMPSS7_CTRIPH
#define mHwPv2CurrHighStat()                XbarRegs.XBARFLG1.bit.CMPSS8_CTRIPH

#define mClearHwBuckBoostCurrDischarHighStat()  XbarRegs.XBARCLR1.bit.CMPSS1_CTRIPH = 1
#define mClearHwBuckBoostCurrCharHighStat()     XbarRegs.XBARCLR1.bit.CMPSS1_CTRIPL = 1

#define mClearHwMidbusVoltHighStat()            XbarRegs.XBARCLR1.bit.CMPSS2_CTRIPH = 1
#define mClearHwInverCurrPosHighStat()          XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPH = 1
#define mClearHwInverCurrNegHighStat()          XbarRegs.XBARCLR1.bit.CMPSS3_CTRIPL = 1


#define mClearHwBusVoltHighStat()               XbarRegs.XBARCLR1.bit.CMPSS4_CTRIPH = 1
#define mClearHwDabLvCurrDisCharHighStat()      XbarRegs.XBARCLR1.bit.CMPSS5_CTRIPH = 1
#define mClearHwDabLvCurrCharHighStat()         XbarRegs.XBARCLR1.bit.CMPSS5_CTRIPL = 1

#define mClearHwDabHvCurrDisCharHighStat()      XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPH = 1
#define mClearHwDabHvCurrCharHighStat()         XbarRegs.XBARCLR1.bit.CMPSS6_CTRIPL = 1

#define mClearHwPv1CurrHighStat()               XbarRegs.XBARCLR1.bit.CMPSS7_CTRIPH = 1
#define mClearHwPv2CurrHighStat()               XbarRegs.XBARCLR1.bit.CMPSS8_CTRIPH = 1


#endif
//
// End of File
//
