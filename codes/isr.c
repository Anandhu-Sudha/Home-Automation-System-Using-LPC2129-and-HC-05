#include<lpc21xx.h>
#include "header.h"

/*
***NOTE flag1 is modified by both UART interrupt and manual sw interrupt
every lcd strings are printed after calculating spaces to clear as well as rewrite the datas based on the req. 
(for manual mode it's "LIGHT ON LIGHT OFF" only, where as in BT mode there's "P    LIGHT ON, NP      LIGHT OFF")
*/

void mode(void) __irq       									
{
	flag2^=1;																													//toggling value of flag when interrupt is triggered
	
	if(flag2==0)																											//flag2==0 (BT Mode)
	{
		lcd_cmd(0x80);
		lcd_string(" Bluetooth Mode ");
		
							if(pairflag==0)																				// for indidcating the pairing status this flag is moonitored in main also. 
							{																											// (if here also not monitored  after changing thte mode the pairing status will get cleared )
								lcd_cmd(0xC0); 
								lcd_string("NP");
							}
							if(pairflag==1)
							{
								lcd_cmd(0xC0); 
								lcd_string(" P");
							}
		
				if(flag1==1)																								// flag1 is the LOAD monitoring flag, depending on this flag do the rest.
						{
							lcd_cmd(0xc3);
							lcd_string("    LIGHT OFF");
						}
				if(flag1==0)
						{
							
							lcd_cmd(0xc3);
							lcd_string("    LIGHT ON ");
						}	
	}
	if(flag2==1)																											// //flag2==1 (Manual Mode)
	{
		lcd_cmd(0x80);
		lcd_string("  Manual  Mode  ");
		
		if(flag1==1)																										// flag1 is the LOAD monitoring flag, depending on this flag do the rest.
		{
			lcd_cmd(0xc0);
			lcd_string("   LIGHT OFF    ");
		}
		if(flag1==0)
		{
			
			lcd_cmd(0xc0);
			lcd_string("   LIGHT ON     ");
		}
		
	}
			
		EXTINT |= 4;								 																		// this is to state the interrupt is serviced.
		VICVectAddr=0;						 																			// clearing vector address.
}


void manual(void) __irq       																			// ISR code.... this code executes, when intr. triggered.
{
	if(flag2==1)																											// only allows to modify the flag1 if it's in manual mode (ie, flag2==1)
	{
		flag1^=1;									 																			//toggling value of flag1 when interrupt is triggered (manual switch)
		if(flag1==1)																										// depending on load status lcd commands also updates here
		{
			lcd_cmd(0xc0);
			lcd_string("   LIGHT OFF    ");
		}
		if(flag1==0)
		{
			
			lcd_cmd(0xc0);
			lcd_string("   LIGHT ON     ");
		}
	}
		
		EXTINT |=1;								 																			// this is to state the interrupt is serviced.
		VICVectAddr=0;						 																			// clearing vector address.
}


void uartisr(void) __irq
{
	
		int v=U0IIR;
		v&=0x0E;
		if(v==4)
		{
			temp=U0RBR;
			flag=1;	
		}
		
		
		if(flag==1)																										  // this is uart's flag (enters the block when data is recieved)
		{
			
			flag=0; 																											// reseting uart's interrupt flag
			if(flag2==0)
			{
				if(temp=='a')
				flag1=0;																										// flag1 is modified here to 0. (ON)
				
				if(temp=='b')
				flag1=1;																										// flag1 is modified here to 1. (OFF)		
			}
			
		if(flag1==1)																										// depending on load status lcd commands also updates here
		{
				lcd_cmd(0xc3);
				lcd_string("    LIGHT OFF");
		}
		if(flag1==0)
		{
							
				lcd_cmd(0xc3);
				lcd_string("    LIGHT ON ");
		}
		
		}
		
		
	VICVectAddr=0;
}

void init_interrupt(void)
{
		// INTERRUPT FOR MANUAL CONTROL
		VICIntEnable= 1<<14;										 // enabling interrupt. here interrupt source 14 (ie, EINT0) is enabling
		VICVectCntl0=(1<<5)|14;									 // 5 bits, 4 lsbs to set the inter. source number, 5 th one to enable the intr.
		VICVectAddr0= (unsigned int)manual;		   // ISR address assigning, name of the (ISR fun)
	
		PINSEL1|=1; 														 // to set p0.16 as interrupt. ( EINT0 )
	  EXTMODE|=1;															 // Edgde mode
		EXTPOLAR|=0;														 // falling edge
	
		// INTERRUPT FOR MODE CONTROL
		VICIntEnable= 1<<16;										 // interrupt source number 16 (ie,EINT2)
	  VICVectCntl1=(1<<5)|16;
	  VICVectAddr1= (unsigned int)mode;
	
		PINSEL0 |= (3 << 14);                    // Enable EINT2 function on P0.7
		EXTMODE |= 4;   									       // Edgde mode
		EXTPOLAR |= 0; 									         // falling edge
	
		// INTERRUPT FOR UART
		VICIntEnable= 1<<6;
		VICVectCntl2= (1<<5)|6;
		VICVectAddr2= (unsigned int)uartisr;
		U0IER=1;

}
