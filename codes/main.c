/* 
P0.18 - Load LED
P0.19	- Manual mode LED
P0.20	- BT Mode LED

P0.9	- STATUS Pin of HC-05
P0.16	- EINT0 for Manual switching (priority 0)
P0.7	- EINT2 for Mode Switching ( M->BT & BT-> M ) (priority 1)
UART0 Interrupt (priority 3)




*/
#define LED1 (1<<19)																								// manual mode indicator
#define LED2 (1<<20)																								// bluetooth mode indicator
#define LED3 (1<<18) 																								// load indicator

#define pair ((IOPIN0>>9)&1)																				//STATUS pin of hc-05 connected to p0.9

#include <lpc21xx.h>
#include "header.h"

volatile int flag2=1,flag1=1,pairflag=0;
unsigned char temp,flag;

void pair_status(void);

int main()
{
	init_interrupt();
	lcd_init();
	uart_init(9600);
	
	lcd_cmd(0x86);																										// Welcome message setting
	lcd_string("HOME");
	lcd_cmd(0xc1);
	lcd_string("AUTOMATION SYS");
	delay_sec(2);																											// for 2 sec.
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("  Manual  Mode  ");																		//  if it's not printed for the very first time , even after the system is on , 
																																		//	there will be no info regarding manual or bt. only it displays after the isr is triggered.
	lcd_cmd(0xc0);
	lcd_string("   LIGHT OFF    ");
	
		IODIR0|=LED2|LED1|LED3;
		IOSET0|=LED2|LED1|LED3;

/* 
***ALL THE FLAGS ARE EXTERN & TOGGLED USING EINTs IN THE ISR FUNCTION.***
	
the flag1 (used for monitoring and Toggling the Load)
the flag2 (used for monitiring and Toggling the Mode)
if the value of these flags are not monitored here, then again these leds won't 
light up the first time after starting, it will only start indicating after one isr execution, 
just like the case of LCD mentioned in the first
*/
	
	while(1)
	{
		
		
		pair_status(); 																									// continuosly monitoring the pairing status.
		
		if(flag2==0)              																			// MODE CHANGING
		{																																// flag2==0 for bluetooth mode
			IOCLR0|=LED2;																									// turning on the coresponding LED
			IOSET0|=LED1;
		}
		if(flag2==1)											
		{																																// flag2==1 for manual mode
			IOCLR0|=LED1;																									// turning on the coresponding LED
			IOSET0|=LED2;
		}
		
		
		if(flag1==0)						  																			// LOAD INDICATOR
		{
			IOCLR0|=LED3;
		}
		if(flag1==1)
		{
			IOSET0|=LED3;
		}
	}
}

void pair_status(void)																							// function for pariring status monitoring (only polling methods effective)
{
    static int prev_status=-1; 																			// previous pairing status
		if(flag2==0)																										// to check if it's bt mode 
		{
					if(pair==0&&prev_status!=0)																// if paired (this extra logic is to avoid the lcd flickering)
						{																												// if it's continuosly printing in the loop it'll cause the screen to flicker. so always write the logic to print in once.
								pairflag=0;
								lcd_cmd(0xC0); 
								lcd_string("NP");																		// NP - not paired
								prev_status=0; 
						}
					else if(pair==1&&prev_status!=1)
						{
								pairflag = 1;
								lcd_cmd(0xC0);
								lcd_string(" P");																		// P - paired
								prev_status = 1; 
						}
		}
}
