#include <detpic32.h>

void delay(int);

int main(void)
{
	TRISE = (TRISE & 0xFFF0);
	
	int count = 0;
	
	while(1)
	{
 		delay(2000);
 		
 		LATE = LATE & 0xFFF0;
 		
 		count++;
 		
 		count = (count & 0x000F);

		LATE = LATE | count;
 	}
 	return 0;
} 

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
