#define F_CPU 16000000UL

extern "C" {
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
};


constexpr uint16_t XXX {23};

void GPIO_Init(); // Nur-Deklaration


int main(void)
{
	auto y = & XXX;
	
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