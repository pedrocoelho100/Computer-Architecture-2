#include <detpic32.h>

void main(void)
{
	// Configure Timer T3 (2 Hz with interrupts disabled)
	
	T3CONbits.TCKPS = 7; // 1:256 prescaler (i.e Fout_presc = 78125 Hz)
 	PR3 = 39061; 		 // Fout = 20MHz / (32 * (x + 1)) = 2 Hz
 						 // PR3 = (78125Hz / 2Hz) – 1 ≅ 39061
 	TMR3 = 0; 			 // Reset timer T3 count register
 	T3CONbits.TON = 1; 	 // Enable timer T3 (must be the last command of the timer configuration sequence)
 
	while(1)
	{
 		while(IFS0bits.T3IF == 1);	// Wait until T3IF = 1
 		IFS0bits.T3IF = 0;			// Reset T3IF
 		putChar('.');
	}
}
