#include <detpic32.h>

void isr_adc(void);
void delay(int);
unsigned char toBCD(unsigned char);
void send2displays(unsigned char);
void configureAll(void);

volatile int voltage = 0; // Global variable

int main(void)
{
	configureAll(); // Function to configure all (digital I/O, analog
					// input, A/D module, timers T1 and T3, interrupts)
	// Reset AD1IF, T1IF and T3IF flags
	IFS1bits.AD1IF = 0;
	IFS0bits.T1IF = 0; 
	IFS0bits.T3IF = 0; 
	
	EnableInterrupts(); // Global Interrupt Enable
	while(1);
}

void configureAll(void){
	
	TRISB = TRISB & 0x00FF;	
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
   	TRISBbits.TRISB4 = 1;
   	AD1PCFGbits.PCFG4 = 0; //desligar entrada analógica RB4  
  	AD1CON1bits.SSRC = 7;    
   	AD1CON1bits.CLRASAM = 1;   
   	AD1CON3bits.SAMC = 16; 
   	AD1CON2bits.SMPI = 7;
   	AD1CHSbits.CH0SA = 4;
   	AD1CON1bits.ON = 1;       

	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0; // Reset AD1IF flag
 	EnableInterrupts(); // Global Interrupt Enable
 	
 	
	// Configure Timers T1 and T3
	// Timer T1 - 4Hz
	T1CONbits.TCKPS = 7; // 1:256 prescaler
   	PR1 = 19530; // Fout = 20MHz / (256 * (19530 + 1)) = 4 Hz 
   	TMR1 = 0;            // Reset timer T1 count register 
   	T1CONbits.TON = 1;   // Enable timer T1

   	IPC1bits.T1IP = 2;   // Interrupt priority
   	IEC0bits.T1IE = 1;   // Enable timer T1 interrupts

	// Timer T3 - 100 Hz
	T3CONbits.TCKPS = 2; // 1:4 prescaler
   	PR3 = 49999; // Fout = 20MHz / (4 * (49999 + 1)) = 100 Hz 
   	TMR3 = 0;            // Reset timer T3 count register 
   	T3CONbits.TON = 1;   // Enable timer T3

    IPC3bits.T3IP = 2;   // Interrupt priority
   	IEC0bits.T3IE = 1;   // Enable timer T3 interrupts
 	
}

void _int_(27) isr_adc(void){

	// Calculate buffer average (8 samples)
	int i, V;
	int media = 0;
	int *p = (int *)(&ADC1BUF0);
	
	for(i = 0; i < 16; i++)
		media += p[i*4];
 	media = media / 8;
    // Calculate voltage amplitude
	V = (media * 99) / 1023;
    
	voltage = toBCD(V);  // Convert voltage amplitude to decimal. Assign it to "value2display"
	
    IFS1bits.AD1IF = 0;   // Reset AD1IF flag 
}

void _int_(4) isr_T1(void) 
{ 
	// Start A/D conversion
	AD1CON1bits.ASAM = 1; 
    // Reset T1IF flag
	IFS0bits.T1IF = 0;
} 

void _int_(12) isr_T3(void) 
{ 
	// Send "voltage" global variable to displays 
	send2displays(voltage);
	// Reset T3IF flag 
	IFS0bits.T3IF = 0;
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
