#define  DisableUart1RxInterrupt()    IEC0bits.U1RXIE = 0;
#define  EnableUart1RxInterrupt()     IEC0bits.U1RXIE = 1; 
#define  DisableUart1TxInterrupt()    IEC0bits.U1TXIE = 0; 
#define  EnableUart1TxInterrupt()     IEC0bits.U1TXIE = 1;
