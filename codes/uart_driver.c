// uart driver file
#include<lpc21xx.h>
#include "header.h"

// initilization
void uart_init(u32 baud)
{
int a[5]={15,60,30,15,15};
u32 result , pclk;
pclk=(a[VPBDIV%4]*1000000);
result=pclk/(16*baud);

PINSEL0|=0x5;

U0LCR=0x83;
U0DLL=result&0xFF;
U0DLM=result>>8;
U0LCR=0x03;
}

// uart tx
#define THRE ((U0LSR>>5)&1)
void uart_tx(u8 data)
{
U0THR=data;
while(THRE==0);
}

// uart rx
#define RDR (U0LSR&1)
u8 uart_rx(void)
{
while(RDR==0);
return U0RBR;
}





