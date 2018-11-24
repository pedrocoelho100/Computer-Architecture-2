#define  DisableUart1RxInterrupt()    IEC0bits.U1RXIE = 0
#define  EnableUart1RxInterrupt()     IEC0bits.U1RXIE = 1
#define  DisableUart1TxInterrupt()    IEC0bits.U1TXIE = 0 
#define  EnableUart1TxInterrupt()     IEC0bits.U1TXIE = 1

#define BUF_SIZE 8

typedef struct
{
	unsigned char data[BUF_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int count;
} circularBuffer;

volatile circularBuffer txb; // Transmission buffer
volatile circularBuffer rxb; // Reception buffer 
