//kpm.c
#include "types.h"
//#include <LPC21xx.h>
#ifndef _LPC2148_
#include <lpc21xx.h>
#else
#include <lpc214x.h>
#endif

#include "defines.h"
#include "kpm_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
u8 kpmLUT[4][4]=
{

	{'1','2','3','/'},
	{'4','5','6','X'},
	{'7','8','9','-'},
	{'C','0','=','+'}

};
void Init_KPM(void)
{
	//cfg row lines as gpio output lines &
	//ground all rows
	WRITENIBBLE(IODIR1,ROWS_4,15);
	//cfg col lines as gpio input(default anyway);
}
u32  colscan(void)
{

	return (READNIBBLE(IOPIN1,COLS_4)<15)? 0 : 1; 
}
u32  rowcheck(void)
{
  u32 r;
  for(r=0;r<=3;r++)
  {
		//ground one row at a time,starting from 0th row
		WRITENIBBLE(IOPIN1,ROWS_4,~(1<<r));
		//check if key was pressed in that row
		if(colscan()==0)
		{
			break;
		}			
  }		
	//re-initiaze all rows to ground
	WRITENIBBLE(IOPIN1,ROWS_4,0);
	return r;
}
u32  colcheck(void)
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(READBIT(IOPIN1,COL0+c)==0)
		{
			break;
		}
	}
	return c;
}
u32  Keyscan(void)
{
	u32 r,c,keyV;
	//wait to detect any key press
	while(colscan());
	//if key press detected
	//identify row in which key was pressed
	r=rowcheck();
	//identify col in which key was pressed
	c=colcheck();
	//map key value to pressed key
	keyV=kpmLUT[r][c];
	return keyV;

}
u32 ReadNum(u32 x)
{	u32 key;
	 u32 num=0;
	 //cmdLCD(GOTO_LINE2_POS0);
	 x=x+1;
	while(x)
	{
		key=Keyscan();
		if((key>='0' && key<='9')||key=='C')
		{
			if((key>='0' && key<='9'))
			{
				num=(num*10)+(key-48);
				//U32LCD(*num);
				while(colscan()==0);
				charLCD(key);
				x--;
			}
			if(key=='C')
			{	//x++;	  
				if(num!=0)
				{
				cmdLCD(SHIFT_DISP_LEFT );
				charLCD(' ');
				cmdLCD(SHIFT_DISP_LEFT );
				num=num/10;
				x++;
				}
				while(colscan()==0);
				//	x++;
					if(num==0)
					{
					x=3;
					cmdLCD(GOTO_LINE2_POS0);
			}		 }
		
		}
		else
		{
			 cmdLCD(CLEAR_LCD);
			 strLCD("updating...");
			 delay_ms(300);
			 cmdLCD(CLEAR_LCD);
				while(colscan()==0);
				break;
		}
	}
 	return num;
}




