#include <detpic32.h>

int main(void)
{
	configUart(115200,'N',1); // default "pterm" parameters
	while(1)
	{
		putc( getc() );
	}
}

char getc(void)
{
	// If OERR == 1 then reset OERR
	// Wait while URXDA == 0
	// If FERR or PERR then
	// read UxRXREG (to discard the character) and return 0
	// else
	// Return U1RXREG
} 
