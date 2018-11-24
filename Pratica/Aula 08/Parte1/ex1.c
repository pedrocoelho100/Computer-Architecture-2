int main(void)
{
	// Configure UART1:
	// 1 - Configure BaudRate Generator
	U1BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
   	U1MODEbits.BRGH = 0;
	// 2 – Configure number of data bits, parity and number of stop bits
	// (see U1MODE register)
	U1MODEbits.PDSEL = 00;
   	U1MODEbits.STSEL = 0;
	// 3 – Enable the trasmitter and receiver modules (see register U1STA)
	U1STAbits.UTXEN = 1;
   	U1STAbits.URXEN = 1;
	// 4 – Enable UART1 (see register U1MODE)
	U1MODEbits.ON = 1;
	
	return 0;
} 
