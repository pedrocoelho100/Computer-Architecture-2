#include <detpic32.h>

void putc(char);
void delay(int);
void configUart(unsigned int, char, unsigned int);

unsigned int i = 0;

int main(void)
{
	configUart(1200, 'O', 2);
	
	while(1)
	{
		puts("String de teste\n");
		delay(1000);	// wait 1 s
	}
	return 0;
} 

void puts(char *str)
{
	// use putc() function to send each charater ('\0' should not be sent)
	if( str[i] != '\0')
		putc(str[i++]);
} 

void putc(char byte2send)
{
	// wait while UTXBF == 1
	while(U1STAbits.UTXBF == 1);
	// Copy byte2send to the UxTXREG register
	U1TXREG = byte2send;
}

void delay(int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
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
