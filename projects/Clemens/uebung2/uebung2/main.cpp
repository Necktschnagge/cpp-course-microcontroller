#define F_CPU 16000000UL

extern "C" {
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
	#include <util/delay.h>
};
void Blink( int number){
	for (int i=0; i < number; i++){
	PORTD |= 0b00000001;
	_delay_ms(500);
	PORTD &= 0b11111110;
	_delay_ms(500);
	}
}

void GPIO_Init();


int main(void)
{
	uint16_t counter {0};
	
	GPIO_Init();

	while (1){
		if (!(PIND & 0b10)) { // wenn taster nicht gedr??
			counter ++;
			Blink(counter);
			}
		else
			Blink(0);
			
		
	}
}


void GPIO_Init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000010;
}