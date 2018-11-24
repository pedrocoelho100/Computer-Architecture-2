#include <detpic32.h>

void isr_adc(void);

int main(void){

// Tempo de Conversão = 3.6 us

//264,4us periodo

// 4.4 us - 3.6 us = 0.8 us

	TRISBbits.TRISB6 = 0;
   	TRISBbits.TRISB4 = 1;
   	AD1PCFGbits.PCFG4 = 0;  
  	AD1CON1bits.SSRC = 7;    
   	AD1CON1bits.CLRASAM = 1;   
   	AD1CON3bits.SAMC = 16; 
   	AD1CON2bits.SMPI = 0;
   	AD1CHSbits.CH0SA = 4;
   	AD1CON1bits.ON = 1;       

	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	EnableInterrupts();
	AD1CON1bits.ASAM = 1;

	while(1){}

}

void _int_(27) isr_adc(void){

	LATBbits.LATB6 = 0;
	printInt(ADC1BUF0, 16 | 3 << 16);
	LATBbits.LATB6 = 1;
	AD1CON1bits.ASAM = 1;
	IFS1bits.AD1IF = 0;

}
