#include <detpic32.h>

int main(void)
{
	int i;
	volatile int aux;
	// Configure A/D module; configure RB6 as a digital output port
	TRISBbits.TRISB6 = 0; 
			
	AD1PCFGbits.PCFG6= 0; 		
	AD1CON1bits.SSRC = 7; 		
	AD1CON1bits.CLRASAM = 1; 	
	AD1CON3bits.SAMC = 16; 		
	AD1CON2bits.SMPI = 0; 		
	AD1CHSbits.CH0SA = 4; 		
	AD1CON1bits.ON = 1;
	
	while(1)
	{
		
		LATBbits.LATB6 = 1;			// Set LATB6
		
		AD1CON1bits.ASAM = 1;		// Start conversion
		
		while(IFS1bits.AD1IF == 0);// Wait while conversion not done (AD1IF == 0)
		
		LATBbits.LATB6 = 0;		// Reset LATB6
	 	
	 	int *p = (int *)(&ADC1BUF0);
		for( i = 0; i < 16; i++ )
		{
			printInt( p[i*4], 10 | 4 << 10 );
			printf(" ");
		}
		
		IFS1bits.AD1IF = 0;		// Reset AD1IF
	}
} 