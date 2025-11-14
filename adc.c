#include<LPC214x.h>
//#include "defines.h"
#include"types.h"
#include"delay.h"
#include"pin_connect_block.h"
#include"pin_function_defines.h"
#include"adc_defines.h"
#include "adc.h"
void Init_ADC(void)
{
	cfgportpinFunc(0,28,pin_fun2);
	AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
	
}
void Read_ADC(u32 chNo,u32 *adcDval,f32 *eAR)
{
	AD0CR&=0XFFFFFF00;
	AD0CR|=(1<<chNo)|(1<<ADC_START_BIT);
	delay_us(3);
	while(((AD0GDR>>DONE_BIT)&1)==0);
	AD0CR&=~(1<<ADC_START_BIT);
	*adcDval=(AD0GDR>>RESULT_BITS)&1023;
	*eAR=(*adcDval *(3.3/1023));
}

