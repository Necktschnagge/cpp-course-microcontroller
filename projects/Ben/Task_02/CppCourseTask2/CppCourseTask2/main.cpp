#define F_CPU 16000000UL

extern "C" {
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
	#include <time.h>
};

/* private defines ---------------------------------------- */

void GPIO_Init();
void LED_Blink();

int main(void)
{
	uint16_t	counter {0};	
	uint16_t	blinker {0};
	uint32_t	timeout {32000000};
	GPIO_Init();
	
	/* Replace with your application code */
	while (1){
		if(!(PIND & 0b10)){						// wenn taster gedrückt
			while(!(PIND & 0b10)){
				_delay_ms(500);
				timeout--;
				if(timeout < 1){
					counter = 0;
				}
			}
			counter++;
			blinker = counter;
		}
		if (blinker > 0){
			LED_Blink();
			blinker--;
			timeout = 4;
		} else {
			PORTD &= 0b11111110;
			timeout = 4;
		}
	}
}

void GPIO_Init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000010;
}

void LED_Blink(){
	PORTD |= 0b00000001;
	_delay_ms(200);
	PORTD &= 0b11111110;
	_delay_ms(200);
}