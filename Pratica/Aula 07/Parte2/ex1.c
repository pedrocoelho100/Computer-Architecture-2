#include <detpic32.h>

int main(void){
	TRISEbits.TRISE0 = 0;
	
   	T3CONbits.TCKPS = 2; // 1:4 prescaler
   	PR3 = 49999;         // Fout = 20MHz / (4 * (49999 + 1)) = 100 Hz 
   	TMR3 = 0;            // Reset timer T3 count register 
   	T3CONbits.TON = 1;   // Enable timer T3
   
   	OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled 
   	OC1CONbits.OCTSEL = 1; // Use timer T3 as the time base for PWM generation 
   	OC1RS = 12500;       // Ton constant 
   	OC1CONbits.ON = 1;   // Enable OC1 module 

   	while(1)
	{
   		LATEbits.LATE0 = 1;
   	}
}
