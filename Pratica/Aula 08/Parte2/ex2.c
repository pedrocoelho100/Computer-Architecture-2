#include <detpic32.h>

volatile int voltage; // Global variable 

void setPWM(unsigned int dutyCycle);
void isr_T1(void);
void putc(char byte2send);
void puts(char *str);
void isr_T3(void);
void isr_adc(void);
unsigned char toBCD(unsigned char);
void send2displays(unsigned char);
void configureAll();
void isr_uart1(void);
void configUart(unsigned int baud, char parity, unsigned int stopbits);

int main(void)
{
	int dutyCycle;
	configureAll();
	EnableInterrupts(); // Global Interrupt Enable
	
	LATEbits.LATE0 = 1;
	
	T3CONbits.TCKPS = 2; // 1:256 prescaler (i.e fin = 78,125 KHz)

							/* configuração da luz */
	PR3 = 49999; 			// Fout = 20MHz / (32 * (39061,5 + 1)) = 2 Hz
	TMR3 = 0; 				// Reset timer T3 count register
	T3CONbits.TON = 1; 		// Enable timer T3 

	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 1;
	OC1CONbits.ON = 1;
	
	while(1)
	{
	
	}
}

void configUart(unsigned int baud, char parity, unsigned int stopbits)
{
	if( baud < 600 || baud > 115200)
		baud = 115200;
	if(parity != 'N' && parity != 'E' && parity != 'O')
		parity = 'N';
	if(stopbits != 1 && stopbits != 2)
    	stopbits = 1;
	
	// Configure number of data bits (8), parity and number of stop bits
	
	U1BRG = ((20000000 + 8 * baud) / (16 * baud)) - 1;
   	U1MODEbits.BRGH = 0;
   	
   	if(parity == 'N')
   		U1MODEbits.PDSEL = 00;
   	else if(parity == 'E')
   		U1MODEbits.PDSEL = 01;
   	else
   		U1MODEbits.PDSEL = 10;
	
   	U1MODEbits.STSEL = stopbits - 1;
   	
	U1STAbits.UTXEN = 1;
   	U1STAbits.URXEN = 1;
   	
	U1MODEbits.ON = 1;	
} 

void putc(char byte2send) 
{ 
   // wait while UTXBF == 1
   while(U1STAbits.UTXBF == 1);
   // Copy byte2send to the UxTXREG register
   U1TXREG = byte2send;
}

void puts(char *str) 
{ 
   // use putc() function to send each charater ('\0' should not be sent)   
   while(str[0] != '\0'){
      putc(str[0]);
      str++;
   }
}

void _int_(24) isr_uart1(void)
{
	if(U1RXREG == 'L')
 	{
 		// Send "voltMin" and "voltMax" to the serial port UART1
 	}
	IFS0bits.U1RXIF = 0;	// Clear UART1 rx interrupt flag 
} 

void setPWM(unsigned int dutyCycle)
{
	// duty_cycle must be in the range [0, 100]
	OC1RS = ((19530+1) * dutyCycle) / 100; // Evaluate OC1RS as a function of "dutyCycle"
} 

void configureAll(void)
{
	TRISEbits.TRISE0 = 0;
	
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	
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

 	
	// Configure Timers T1 and T3
	// Timer T1 - 100Hz
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
	
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0; // Reset AD1IF flag
	EnableInterrupts();
}

void _int_(27) isr_adc(void){

	// Calculate buffer average (8 samples)
	int i, V;
	int media = 0;
	int *p = (int *)(&ADC1BUF0);
	for(i = 0; i < 8; i++)
		media += p[i*4];
 	media = media / 8;
	// Calculate voltage amplitude
	V = (media * 33) / 1023;
	// Convert voltage amplitude to decimal. Copy it to "voltage" 
	voltage = toBCD(V);
	// Reset AD1IF flag
	IFS1bits.AD1IF = 0;
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
	static int counter = 0;
	send2displays(voltage);	// Send "value2display" global variable to displays
	if(++counter == 100)
	{
		counter = 0;
		// send voltage to the serial port UART1
		puts("Voltage: ");
		printInt10(voltage);
		putc('\n');
	}
	IFS0bits.T3IF = 0;	// Clear T3 interrupt flag 
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
