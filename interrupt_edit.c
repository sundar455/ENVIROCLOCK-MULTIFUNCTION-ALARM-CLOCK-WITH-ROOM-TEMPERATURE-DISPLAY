#include"types.h"
#include"delay.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"kpm_defines.h"
#include"kpm.h"
#ifndef _LPC2148_
#include <lpc21xx.h>
#else
#include <lpc214x.h>
#endif

#include"pin_function_defines.h"
#include"pin_connect_block.h"
#include"rtc.h"
#include"rtc_defines.h"
#define EINT0_VIC_CHNO 14
void eint0_isr(void)__irq;
s32 check;
u32 i=0;
u32 minute,second;
extern s32 hour,min,sec,date,month,year,day;
extern u32 adcDval,temp,alaram_hour,alaram_min,flag;
extern u32 key;
void Init_interrupt(void)
{
	Init_LCD();
	Init_KPM();
	cfgportpinFunc(0,1,EINT0_0_1);
	VICIntEnable=1<<EINT0_VIC_CHNO;
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	VICVectAddr0=(u32)eint0_isr;
	EXTMODE=1<<0;

}
void menu()
{
	while(1)
	{
o:      cmdLCD(CLEAR_LCD);
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("1.Time2.Dt3.Day");
	cmdLCD(GOTO_LINE2_POS0);
	strLCD("4.SETALRM 5.EXIT");
	key=Keyscan();
	while(colscan()==0);
	if(key=='1')
	{
l:cmdLCD(CLEAR_LCD);
  cmdLCD(GOTO_LINE1_POS0);
  strLCD("1.Hour  2.mins");
  cmdLCD(GOTO_LINE2_POS0);
  strLCD("3.sec 4.exit");
  key=Keyscan();
  while(colscan()==0);
  if(key=='1')
  {
	  cmdLCD(CLEAR_LCD);
	  cmdLCD(GOTO_LINE1_POS0);
	  strLCD("Enter hour(0-23)");
	  cmdLCD(GOTO_LINE2_POS0);
	  check=ReadNum(2);
	  if(check>=0 && check<=23)
	  {
		  hour=check;
		  SetRTCTimeInfo(hour,min,sec);

		  // while(colscan()==0);^M
		  goto l;
	  }
	  else
	  {
		  cmdLCD(CLEAR_LCD);
		  cmdLCD(GOTO_LINE1_POS0);
		  strLCD("INVALID INPUT");
		  delay_ms(400);
		  //goto l;
	  }
	  goto l;
  }

  else if(key=='2')
  {
	  cmdLCD(CLEAR_LCD);
	  cmdLCD(GOTO_LINE1_POS0);
	  strLCD("Enter min(0-59");
	  cmdLCD(GOTO_LINE2_POS0);
	  check=ReadNum(2);
	  if(check>=0 && check<=59)
	  {
		  min=check;
		  SetRTCTimeInfo(hour,min,sec);
		  while(colscan()==0);
	  }
	  else
	  {
		  cmdLCD(CLEAR_LCD);
		  cmdLCD(GOTO_LINE1_POS0);
		  strLCD("INVALID INPUT");
		  delay_ms(400);
		  //goto l;
	  }
	  goto l;
  }

  else if(key=='3')
  {
	  cmdLCD(CLEAR_LCD);
	  cmdLCD(GOTO_LINE1_POS0);
	  strLCD("Enter sec(0-59");
	  cmdLCD(GOTO_LINE2_POS0);
	  check=ReadNum(2);
	  if(check>=0 && check<60)
	  {
		  sec=check;
		  SetRTCTimeInfo(hour,min,sec);
		  //while(colscan()==0);
	  }
	  else
	  {
		  cmdLCD(CLEAR_LCD);
		  cmdLCD(GOTO_LINE1_POS0);
		  strLCD("INVALID INPUT");
		  delay_ms(400);
		  //goto l;
	  }
	  goto l;

  }

  else if(key=='4')
  {
	  //    return ;
	  goto o;
  }
  else
  {
	  cmdLCD(CLEAR_LCD);
	  cmdLCD(GOTO_LINE1_POS0);
	  strLCD("INVALID INPUT");
	  delay_ms(400);
	  goto l;
  }     //break;
	}
	else if(key=='2')
	{
k:      cmdLCD(CLEAR_LCD);
	cmdLCD(GOTO_LINE1_POS0);
	strLCD("1.date  2.month");
	cmdLCD(GOTO_LINE2_POS0);
	strLCD("3.year 4.EXIT");
	key=Keyscan();
	while(colscan()==0);
	if(key=='1')
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("Enter date(1-31");
		cmdLCD(GOTO_LINE2_POS0);
		check=ReadNum(2);
		if(check>=1 && check<=31)
		{
			date=check;
			SetRTCDateInfo(date,month,year);
		}
		else
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("INVALID INPUT");
			delay_ms(400);
			//goto k;
		}
		goto k;
	}
	else if(key=='2')
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("Enter Month(1-12");
		cmdLCD(GOTO_LINE2_POS0);
		check=ReadNum(2);
		if(check>=1 && check<=12)
		{
			month=check;
			SetRTCDateInfo(date,month,year);
		}
		else
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("INVALID INPUT");
			delay_ms(400);
			//goto k;
		}
		goto k;
	}

	else if(key=='3')
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("Enter Year(upto 3000");
		cmdLCD(GOTO_LINE2_POS0);
		check=ReadNum(4);
		if(check>=2000 && check<=3000)
		{
			year=check;
			SetRTCDateInfo(date,month,year);
		}
		else
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("INVALID INPUT");
			delay_ms(400);
			//      goto k;
		}
		goto k;
	}
	else if(key=='4')
	{
		//return ;
		goto o;
	}
	else
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("INVALID INPUT");
		delay_ms(400);
		goto k;
	}       //break;
	}
	else if(key=='3')
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("ENTER(0-7)FOR");
		cmdLCD(GOTO_LINE2_POS0);
		strLCD("(sun-sat):");
		cmdLCD(GOTO_LINE2_POS0+11);
		check=ReadNum(1);
		if(check>=0&& check<7)
		{
			cmdLCD(CLEAR_LCD);
			day=check;
			SetRTCDay(day);
			//return;

		}
		else
		{
			cmdLCD(CLEAR_LCD);
			cmdLCD(GOTO_LINE1_POS0);
			strLCD("INVALID INPUT");
			delay_ms(400);
			//return;
			//goto l;
		}
		goto o;

	}
	else if(key=='4')
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
h: strLCD("1.Time 2.min");
   cmdLCD(GOTO_LINE2_POS0);
   strLCD("3.EXIT");
   key=Keyscan();
   while(colscan()==0);
   if(key=='1')
   {
	   cmdLCD(CLEAR_LCD);
	   cmdLCD(GOTO_LINE1_POS0);
	   strLCD("Enter Hour:");
	   cmdLCD(GOTO_LINE2_POS0);
	   check=ReadNum(2);
	   if(check>=0 && check<=23)
	   {
		   alaram_hour=check;
		   goto h;
	   }
	   else
	   {
		   cmdLCD(CLEAR_LCD);
		   cmdLCD(GOTO_LINE1_POS0);
		   strLCD("INVALID INPUT");
		   delay_ms(400);
		   goto h;
	   }
   }
   else if(key=='2')
   {
	   cmdLCD(CLEAR_LCD);
	   cmdLCD(GOTO_LINE1_POS0);
	   strLCD("Enter Min:");
	   check=ReadNum(2);
	   if(check>=0 && check<=59)
	   {
		   alaram_min=check;
		   //goto h;
	   }
	   else
	   {
		   cmdLCD(CLEAR_LCD);
		   cmdLCD(GOTO_LINE1_POS0);
		   strLCD("INVALID INPUT");
		   delay_ms(400);
		   goto h;
	   }
	   cmdLCD(CLEAR_LCD);
	   strLCD("ALARAM SET!");
	   delay_s(1);
	   cmdLCD(CLEAR_LCD);
	   //return;
	   goto o;
   }
   else
   {
	   goto o;
   }
	}
	else if(key=='5')
	{
		cmdLCD(CLEAR_LCD);
		while(colscan()==0);
		return;
	}
	else
	{
		cmdLCD(CLEAR_LCD);
		cmdLCD(GOTO_LINE1_POS0);
		strLCD("INVALID INPUT!");
		delay_ms(400);
	}
	}
}
void eint0_isr(void)__irq
{
	Init_KPM();
	menu();
	EXTINT=1<<0;
	VICVectAddr=0;
}

