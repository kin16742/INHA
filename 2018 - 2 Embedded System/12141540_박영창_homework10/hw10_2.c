#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define ON 1
#define OFF 0

int data[8] = {17,43,66,77,97,114,129,137};
volatile int state = OFF;
volatile int idx = 0;
volatile int onoff = OFF;

ISR(INT4_vect)
{
	if(onoff == OFF) onoff = ON;
	else if (onoff == ON) onoff = OFF;
}

ISR(INT5_vect)
{
	idx++;
}

ISR(TIMER0_OVF_vect){
    if(onoff==ON){
		if(state==ON){
			PORTB=0x00;
			state=OFF;
		}
		else{
			PORTB=0x10;
			state=ON;
		}
		TCNT0=data[idx%8];
	}
}

int main()
{
	DDRB = 0x10;
	DDRG = 0x10;
	DDRE = 0xcf; 

	EICRB = 0x0A; 
	EIMSK = 0x30; 
	TCCR0 = 0x03;
	TIMSK = 0x01;
	TCNT0 = data[0];
	sei();
	
	while(1);
}
