/*
 * DisplayTransmit.cpp
 *
 * Created: 29.01.2018 15:16:30
 * Author : bmuch
 */ 

#include "display.h"
#include <avr/io.h>

void timer_start(){
	TCCR1B = 0b101;						// set prescaler to 1024 and start timer
}

void timer_stop(){
	TCCR1B = 0b000;						// stop timer
	TCNT1H = 0;
	TCNT1L = 0;
}

uint16_t timer_read(){
	return (TCNT1H << 8) + TCNT1L;
}

char tx_buffer[] = "Hallo";
uint32_t time_stamp = 0;

int main(void)
{
	GPIO_Init();
	connect();
	
    /* Replace with your application code */
    while (1) 
    {	
		timer_start();
		if(timer_read() > (1024*16)){
			clear_screen();
			send_int(time_stamp);
			timer_stop();
			time_stamp++;
		}
    }
}

