#include <detpic32.h>

void delay(int);

int main(void)
{
	unsigned char segment;
	LATDbits.LATD6 = 1; // display high active
	LATDbits.LATD5 = 0; // display low inactive
						// configure RB8-RB14 as outputs
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;
	
	TRISDbits.TRISD6 = 0; // configure RD5-RD6 as outputs
	TRISDbits.TRISD5 = 0;
	while(1)
	{
		LATDbits.LATD6 = !LATDbits.LATD6; 	//
		LATDbits.LATD5 = !LATDbits.LATD5; 	// toggle display selection
		segment = 1;
		int i;
		for(i=0; i < 7; i++)
		{
	 		// send "segment" value to display
 			LATB = (LATB & 0x80FF) | (segment << 8);
 			
 			segment = segment << 1;
 			
 			delay(100);	// wait 1 second
 		}
 	}
 	return 0;
} 

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
