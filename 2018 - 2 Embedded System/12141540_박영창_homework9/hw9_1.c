#include <avr/io.h>  
#include <util/delay.h>

int main(){
	unsigned char value = 128;
	int flag = 0;

	DDRA = 0xff;
 	
	for(;;){
		PORTA=value;
		_delay_ms(500);
		
		if(!flag)	value>>=1;
		if(flag)	value<<=1;
		
		if		(value==0)		{flag = 1; value = 1;}
		else if	(value==128)	{flag = 0;}
 	}
 }