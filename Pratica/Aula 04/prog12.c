#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);

int main(void)
{
	
 	// configure RB8 to RB14 and RD5 to RD6 as outputs
 	LATB = LATB & 0x80FF;
 	TRISB = TRISB & 0x80FF;
 	
 	TRISDbits.TRISD5 = 0;
 	TRISDbits.TRISD6 = 0;
	int x = 0;
	unsigned char disp;
 	while(1)
 	{	
 		int i = 0;
	 	do
	 	{
	 		delay(50);
	 		disp = (x & 0xFF);
	 		send2displays(disp);
 		}while(++i < 4);
 		x++;
 	} 
 	return 0;
} 

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
	
	static unsigned char displayFlag = 0;
	
	unsigned char first = value & 0x0F;
	first = display7Scodes[first];
	unsigned char second = value >> 4;
	second = display7Scodes[second];
 	
 	if(!displayFlag) 		// send digit_high to display_high
 	{
 		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;
 		LATB = (LATB & 0x80FF) | (first << 8);
 	}
 	else 			 		// send digit_low to display_low
 	{
 		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 0;
 		LATB = (LATB & 0x80FF) | (second << 8);
 	}
 	displayFlag = !displayFlag;
} 

void delay(int ms) 
{ 
   	for(; ms > 0; ms--) 
   	{ 
     	resetCoreTimer(); 
      	while(readCoreTimer() < 20000); 
   	} 
}
