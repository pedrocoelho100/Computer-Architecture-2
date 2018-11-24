#include <detpic32.h>

void delay(int);
void send2displays(unsigned char);
unsigned char toBCD(unsigned char);

void main(void)
{
	// Configure all (digital I/O, analog input, A/D module)
	
	TRISB = TRISB & 0x00FF;
	TRISDbits.TRISD5 = 0; 
	TRISDbits.TRISD6 = 0; 
	
	TRISBbits.TRISB4 = 1; 
			
	AD1PCFGbits.PCFG4= 0; 		
	AD1CON1bits.SSRC = 7; 		
	AD1CON1bits.CLRASAM = 1; 	
	AD1CON3bits.SAMC = 16; 		
	AD1CON2bits.SMPI = 3; 		
	AD1CHSbits.CH0SA = 4; 		
	AD1CON1bits.ON = 1;
	
	int i = 0;
	int V;
	int media;
	while(1)
	{
		delay(10);					// Wait 10 ms using the core timer
		if(++i == 25) // 250 ms
		{
			// Convert analog input (4 samples)
			
			// Start conversion
			AD1CON1bits.ASAM = 1;
         		
			// Wait while conversion not done (AD1IF == 0)
			while(IFS1bits.AD1IF == 0);

            // Calculate buffer average 
			int *p = (int *)(&ADC1BUF0);
			media = 0;
			int j;
			for( j = 0; j < 4; j++ )
			{
				media += p[j*4];
			}
			media = media / 4;

            // Calculate voltage amplitude
			V = (media * 33) / 1023; 

		    // Reset AD1IF
			IFS1bits.AD1IF = 0;   	  		
	
			// Convert voltage amplitude to decimal 
			V = toBCD(V); 
			i = 0;
		}
		send2displays(V);
	}
} 

void delay(int ms)
{ 
	for(; ms > 0; ms--) 
	{ 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
	} 
}

unsigned char toBCD(unsigned char value){

	return ((value / 10) << 4) + (value % 10);

}

void send2displays(unsigned char value) 
{ 

	static const char display7Scodes[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
	
	static unsigned char displayFlag = 0;
	
	unsigned char first = value & 0x0F;
	first = display7Scodes[first];
	unsigned char second = value >> 4;
	second = display7Scodes[second];
	
	if(!displayFlag){ // send digit_high to display_high
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		LATB = (LATB & 0x00FF) | first<<8;
		
	
	}else{ // send digit_low to display_low
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		LATB= (LATB & 0x00FF) | second<<8;
		
	}
	displayFlag = !displayFlag;
} 
