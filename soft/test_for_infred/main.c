#include "reg51.h"
#include "intrins.h"
#include "infred.h"

void main()
{
	char a[]="123";
	int delay=0 ;
	infred_init();
	
	
	
	while (1)
	{
		infred_send(a,3);
		// char b ;
		// b=0x83;
		// infred_send_byte(b);
		delay=0 ;
		do{
			delay++;
		}while(delay<30000);
		
		// infred_send_bit(0x01);
		// delay=0 ;
		// do{
			// delay++;
		// }while(delay==100);
		// infred_send_bit(0x00);
		// delay=0 ;
		// do{
			// delay++;
		// }while(delay==100);
	}
	
}