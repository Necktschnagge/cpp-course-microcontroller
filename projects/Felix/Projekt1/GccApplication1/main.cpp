/*
 * GccApplication1.cpp
 *
 * Created: 06.11.2017 16:38:28
 * Author : Felix
 */ 

#include <avr/io.h>

void GPIO_Init();


int main(void)
{
	uint16_t counter {0};
	uint16_t counter2 {0};
		
	GPIO_Init();
    /* Replace with your application code */
    while (1) 
    {
		if(counter2>20){
			while (i<=counter)
			PORTD |=0b00000001; //einschalten
			_delay_ms(500)
			PORTD &= 0b11111110 ;//ausschalten
			}else if(PIND & 0b1){
			counter ++;
			}else if (PIND & 0b10){
			counter2 ++
			_delay_ms(500)
		}
	}


void GPIO_Init(){
	DDRD |=0b00000001;
	PORTD |= 0b00000010;
}




