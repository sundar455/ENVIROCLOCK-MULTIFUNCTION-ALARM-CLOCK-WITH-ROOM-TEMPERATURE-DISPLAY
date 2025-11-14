#include"types.h"
void delay_us(u32 diyus)
{
	diyus*=12;
	while(diyus--);
}
void delay_ms(u32 diyms)
{
diyms*=12000;
while(diyms--);
}
void delay_s(u32 diys)
{
diys*=12000000;
while(diys--);
}


