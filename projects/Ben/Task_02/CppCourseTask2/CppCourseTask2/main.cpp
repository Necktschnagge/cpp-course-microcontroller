#define F_CPU 16000000UL

extern "C" {
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
};


void GPIO_Init();


int main(void)
{
	uint16_t counter {0};
	
	GPIO_Init();
	
	/* Replace with your application code */
	while (1){
		if (PIND & 0b10) { // wenn taster nicht gedrückt
			PORTD &= 0b11111110;
		} else {
			PORTD |= 0b00000001;	
		}		
	}
}

void GPIO_Init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000010;
}