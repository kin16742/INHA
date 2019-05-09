#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char fnd_sle[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

int main(){
	int num = 0;

	DDRA = 0xff;
 	DDRC = 0xff;
 	DDRG = 0x0f;

 	while(1){
		num = rand() % 8;
		PORTA = fnd_sle[num % 8];
 		PORTC = digit[num % 8];
 		PORTG = 0xff;
 		_delay_ms(10000);
 	}
}
