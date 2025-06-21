//modified for 4 bit to work in vector board
// d4-d7 -> p0.2-p0.5
// rs-6,rw-7,en=8
#include<lpc21xx.h>
#include "header.h"

void lcd_data(unsigned char data)
{
//higher nibble
unsigned int temp;
IOCLR0=0x000001FC;
temp=(data & 0xF0)>>2;
IOSET0=temp;

IOSET0=1<<6; //RS=1
IOCLR0=1<<7;
IOSET0=1<<8;
delay_ms(2);
IOCLR0=1<<8;

//lower nibble
IOCLR0=0x000001FC;
temp=(data & 0x0F)<<2;
IOSET0=temp;

IOSET0=1<<6; //RS=1
IOCLR0=1<<7;
IOSET0=1<<8;
delay_ms(2);
IOCLR0=1<<8;

}

void lcd_cmd(unsigned char cmd)
{
//higher nibble
unsigned int temp;
IOCLR0=0x000001FC;
temp=(cmd & 0xF0)>>2;
IOSET0=temp;

IOCLR0=1<<6; //RS=1
IOCLR0=1<<7;
IOSET0=1<<8;
delay_ms(2);
IOCLR0=1<<8;

//lower nibble
IOCLR0=0x000001FC;
temp=(cmd & 0x0F)<<2;
IOSET0=temp;

IOCLR0=1<<6; //RS=1
IOCLR0=1<<7;
IOSET0=1<<8;
delay_ms(2);
IOCLR0=1<<8;

}

void lcd_init()
{
IODIR0=0x000001FC;
//PINSEL0=0x0;
IOCLR0=1<<8;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x01);

}

void lcd_string( char *ptr)		// lcd string printing
{
while(*ptr!=0)
{
 lcd_data(*ptr);
 ptr++;
}
}

void lcd_cgram(void)  // custom character generator
{
 int i;
 unsigned char a[8]={0x1F,0x04,0x04,0x1F,0x04,0x04,0x1F,0x00};
 lcd_cmd(0x48);
 for(i=0;i<8;i++)
 {
 lcd_data(a[i]);
 }
}


