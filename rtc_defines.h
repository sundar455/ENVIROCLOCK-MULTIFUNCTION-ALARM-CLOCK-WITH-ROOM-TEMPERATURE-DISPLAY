#ifndef RTC_DEFINES_H

#define RTC_DEFINES_H


// System clock and peripheral clock Macros

#define FOSC 12000000

#define CCLK (5*FOSC)

#define PCLK (CCLK/4)

#define _LPC2148_ 
// RTC Macros
 #ifndef _LPC2148_
#define PREINT_VAL ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))
#endif
#define RTC_ENABLE (1<<0) 
#define RTC_RESET  (1<<1)   


#endif

