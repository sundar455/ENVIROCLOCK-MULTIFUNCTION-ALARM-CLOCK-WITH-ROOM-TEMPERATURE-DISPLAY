#ifndef _LPC2148_
#include <lpc21xx.h>
#else
#include <lpc214x.h>
#endif

#include "types.h"
//include LCD header files
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "delay.h"
#include "adc.h"
#include "adc_defines.h"
void Init_interrupt(void);
s32 hour,min,sec,date,month,year,day;
u32 key;
u32 adcDval,temp,chNo=1;
s32 alaram_hour=-1,alaram_min=-1;
f32 eAR;
u8 alaramLUT[8]=
{
	0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x00,0x00
};
int main()
{

	Init_LCD();
	Init_ADC();
	RTC_Init();
//	SetRTCTimeInfo(19,30,00);
//	SetRTCDateInfo(18,10,2025);
	SetRTCDay(6);
	Init_interrupt();
	IODIR0|=1<<20;
	while (1)
	{
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
		//U32LCD(12);
		Read_ADC(chNo,&adcDval,&eAR);
		temp=eAR*100;
		cmdLCD(GOTO_LINE2_POS0+12);
		//U32LCD(12);
		U32LCD(temp);
		charLCD(0xDF);
		charLCD('C');
		if(((IOPIN0>>22)&1)==0)
		{
			IOCLR0=1<<20;
			alaram_hour=-1;
			alaram_min=-1;
		}
		if(HOUR==alaram_hour&& MIN==alaram_min)
		{
			IOSET0=1<<20;
			//cmdLCD(CLEAR_LCD);
			cmdLCD(DSP_ON_CUR_BLINK);
			BUILDCGRAM(alaramLUT,8);
			cmdLCD(GOTO_LINE1_POS0+15);
			charLCD(0);
			//cmdLCD(DSP_ON_CUR_BLINK);
			//delay_ms(10);
			charLCD(1);
			//delay_s(3);
			//flag=0;
		}
		else
		{
			IOCLR0=1<<20;
			cmdLCD(GOTO_LINE1_POS0+15);
			charLCD(' ');
		}											
	}
}

