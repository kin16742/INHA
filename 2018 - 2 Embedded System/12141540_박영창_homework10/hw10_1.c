#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char digit[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char fnd_sel[4]={0x01,0x02,0x04,0x08};
volatile int cnt = 0;
volatile int count =0;

ISR(INT4_vect)
{
	count++;
}

ISR(INT5_vect)
{
	cnt = 0;
}

void display_fnd()
{
 		PORTC=digit[cnt % 10];
 		PORTG=fnd_sel[0];
		_delay_us(2500);

		PORTC=digit[(cnt / 10) % 10];
 		PORTG=fnd_sel[1];
		_delay_us(2500);
 	
		PORTC=digit[(cnt / 100) % 10] + 0x80;
 		PORTG=fnd_sel[2];
		_delay_us(2500);
 	
		PORTC=digit[(cnt / 1000) % 6];
 		PORTG=fnd_sel[3];
		_delay_us(2500);
}

int main()
{
	DDRC = 0xff; 
	DDRG = 0x0f;  
	DDRE = 0xcf; 

	EICRB = 0x0A;  
	EIMSK = 0x30;  
	SREG |= 1<<7; 
	
	while(1) { 	 	
		if(count%2){
			cnt++;
		}
		display_fnd();
	}


}


