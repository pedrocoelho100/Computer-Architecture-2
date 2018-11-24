#include <detpic32.h>

void putc(char);
void delay(int);

unsigned int i = 0;

int main(void)
{
	// Configure UART1 (115200, N, 8, 1)
	U1BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
   	U1MODEbits.BRGH = 0;
	U1MODEbits.PDSEL = 00;
   	U1MODEbits.STSEL = 0;
	U1STAbits.UTXEN = 1;
   	U1STAbits.URXEN = 1;
	U1MODEbits.ON = 1;
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
