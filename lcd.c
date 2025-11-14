#include<LPC21xx.h>
#include"types.h"
#include"defines.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"delay.h"
void cmdLCD(u8 cmd)
{
	IOCLR0=1<<LCD_RS;
	WriteLCD(cmd);
}
void WriteLCD(u8 byte)
{
IOCLR0=1<<LCD_RW;
WRITEBYTE(IOPIN0,LCD_DATA,byte);
IOSET0=1<<LCD_EN;
delay_ms(1);
IOCLR0=1<<LCD_EN;
delay_ms(2);
}
void Init_LCD(void)
{
IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
delay_ms(15);
cmdLCD(0x30);
delay_ms(4);
delay_us(100);
cmdLCD(0x30);
delay_us(100);
cmdLCD(0x30);
cmdLCD(MODE_8BIT_2LINE);
cmdLCD(DSP_ON_CUR_ON);
cmdLCD(CLEAR_LCD);
cmdLCD(SHIFT_CUR_RIGHT);
}
void charLCD(u8 asciiVal)
{
	IOSET0=1<<LCD_RS;
	WriteLCD(asciiVal);
}
void strLCD(s8 *str)
{
	while(*str)
	{
	charLCD(*str++);
	}
}
void U32LCD(u32 n)
{
	s32 i=0;
	u8 a[10];
	if(n==0)
	{
		charLCD('0');
	}
	else
	{
		while(n>0)
		{
		a[i++]=(n%10)+48;
		n/=10;
		}
		for(--i;i>=0;i--)
		{
		charLCD(a[i]);
		}
	}
}
void S32LCD(s32 num)
{
	if(num<0)
	{
		charLCD('-');
		num=-num;
	}
	U32LCD(num);
}
void F32LCD(f32 fnum,u32 nDP)
{
	u32 num,i;
	if(fnum<0.0)
	{
	charLCD('-');
	fnum=-fnum;
	}
	num=fnum;
	U32LCD(num);
	charLCD('.');
	for(i=0;i<nDP;i++)
	{
		fnum=(fnum-num)*10;
		num=fnum;
		charLCD(num+48);
	}
}

void BUILDCGRAM(u8 *p,u8 nbytes)
{
	u32 i;
	cmdLCD(GOTO_CGRAM_START);
	IOSET0=1<<LCD_RS;
	for(i=0;i<nbytes;i++)
	{
	WriteLCD(p[i]);
	}
	cmdLCD(GOTO_LINE1_POS0);
}
