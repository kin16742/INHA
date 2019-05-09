#include <avr/io.h> 
#include <util/delay.h> 

unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char fnd_sle[4] = {0x01, 0x02, 0x04, 0x08};

int main(){
	int cnt = 0;

 	DDRC = 0xff;
 	DDRG = 0x0f;

 	while(1){
 			PORTC=digit[cnt++ % 10];
 			PORTG=fnd_sle[0];
 			_delay_ms(40);

			PORTC=digit[(cnt / 10) % 10];
 			PORTG=fnd_sle[1];
 			_delay_ms(40);
 
			PORTC=digit[(cnt / 100) % 10] + 0x80;
 			PORTG=fnd_sle[2];
 			_delay_ms(40);
 	
			PORTC=digit[(cnt / 1000) % 6];
 			PORTG=fnd_sle[3];
 			_delay_ms(40);
	}
 }