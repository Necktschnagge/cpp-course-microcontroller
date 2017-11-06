#define F_CPU 16000000UL

extern "C" {
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
};

/* private defines ---------------------------------------- */
#define Button_Low			(PORTD & 0b00000010)
#define LED_ON				(PORTD |=0b00000001)

void GPIO_Init();


int main(void)
{
	uint16_t counter = 0;	
	GPIO_Init();
	
	/* Replace with your application code */
	while (1){
		if(Button_Low){
			counter++;
			LED_ON;			
		}
		else
		LED_OFF;
		
	}
}

void GPIO_Init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000010;
}