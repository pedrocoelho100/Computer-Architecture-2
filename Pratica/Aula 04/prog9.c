#include <detpic32.h>

int main(void)
{
	unsigned char display;
 	static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
 	// configure RB0 to RB3 as inputs
 	TRISB = TRISB | 0x000F;
 	
 	// configure RB8 to RB14 and RD5 to RD6 as outputs
 	LATB = LATB & 0x80FF;
 	TRISB = TRISB & 0x80FF;
 	
 	TRISDbits.TRISD5 = 0;
 	TRISDbits.TRISD6 = 0;
 	
 	// Select display low
 	LATDbits.LATD6 = 1; // display high active
	LATDbits.LATD5 = 0; // display low inactive
	
 	while(1)
 	{
 		// read dip-switch
 		int num = PORTB & 0x000F;
 		// convert to 7 segments code
 		display = display7Scodes[num];
 		// send to display
 		LATB = (LATB & 0x80FF) | (display << 8);
 	} 
 	return 0;
} 
