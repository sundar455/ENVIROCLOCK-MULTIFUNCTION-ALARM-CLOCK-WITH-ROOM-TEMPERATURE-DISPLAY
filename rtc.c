#include "rtc_defines.h"
//#include <LPC21xx.H>
#ifndef _LPC2148_
#include <lpc21xx.h>
#else
#include <lpc214x.h>
#endif

#include "rtc_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "types.h"
// Array to hold names of days of the week

s8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
/*

Initialize the Real-Time Clock (RTC)

This function disables the RTC, sets the prescaler values, 

and then enables the RTC.

*/

void RTC_Init(void) 

{

  // Disable and reset the RTC

	CCR = RTC_RESET;

  

  // Set prescaler integer and fractional parts
	#ifndef _LPC2148_
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  // Enable the RTC
	CCR = RTC_ENABLE;
	#else
	CCR=(1<<4)|(1<<0);
	#endif
}
/*

Get the current RTC time

hour Pointer to store the current hour

minute Pointer to store the current minute

second Pointer to store the current second

*/

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{

	*hour = HOUR;

	*minute = MIN;

	*second = SEC;


}


/*

Display the RTC time on LCD

hour value (0 23)

minute value (0 59)

second value (0 59) seperated by ':'

*/

void DisplayRTCTime(s32 hour, s32 minute, s32 second)

{

		cmdLCD(GOTO_LINE1_POS0);

		charLCD((hour/10)+48);

		charLCD((hour%10)+48);

		charLCD(':');

		charLCD((minute/10)+0x30);

		charLCD((minute%10)+0x30);

		charLCD(':');

		charLCD((second/10)+'0');

		charLCD((second%10)+'0');


}


/*

Get the current RTC date

date Pointer to store the current date (1 31)

month Pointer to store the current month (1 12)

year Pointer to store the current year (four digits)

*/

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{

	*date = DOM;

	*month = MONTH;

	*year = YEAR;

}


/*

Display the RTC date on LCD

Date of month (1 31)

Month (1 12)

Year (four digits) and seperated by '/'

*/

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

		cmdLCD(GOTO_LINE2_POS0);

		charLCD((date/10)+48);

		charLCD((date%10)+48);

		charLCD('/');

		charLCD((month/10)+0x30);

		charLCD((month%10)+0x30);

		charLCD('/');

		U32LCD(year);	


}


/*

Set the RTC time

Hour to set (0 23)

Minute to set (0 59)

Second to set (0 59)

*/

void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;


}


/*

Set the RTC date

date of month to set (1 31)

month to set (1 12)

year to set (four digits)

*/

void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

	DOM = date;

	MONTH = month;

	YEAR = year;


}


/*

Get the current day of the week

dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)

*/

void GetRTCDay(s32 *dayofweek)

{

	*dayofweek = DOW; 

}


/*

Display the current day of the week on LCD

dow (Day of Week) (0=Sunday, ..., 6=Saturday)

*/

void DisplayRTCDay(u32 dayofweek)

{

	cmdLCD(GOTO_LINE1_POS0+10);

	strLCD(week[dayofweek]);  

}


/*

Set the day of the week in RTC

Day of Week to set (0=Sunday, ..., 6=Saturday)

*/

void SetRTCDay(u32 dayofweek)

{

		DOW = dayofweek;

}
