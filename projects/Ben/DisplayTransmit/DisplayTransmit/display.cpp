/* 
* display.cpp
*
* Created: 22.03.2018 13:07:34
* Author: bmuch
*/
#include <avr/io.h>
#include "display.h"

uint8_t position = 0;

enum class Output : uint8_t {
	LATCH	= 0b100,
	DATA	= 0b010
};

void GPIO_Init(){
	DDRD |= 0b00000110;
}
bool read_confirm(){
	return (PIND & 0b00000001);
}
void set_output(bool bit, Output out){
	if(bit)
	PORTD |= static_cast<uint8_t>(out);
	else
	PORTD &= ~static_cast<uint8_t>(out);
}
void send_bit(bool tx_bit){
	while(read_confirm() != false){
	}
	set_output(tx_bit, Output::DATA);
	set_output(1, Output::LATCH);
	while(read_confirm() != true){
	}
	set_output(0, Output::LATCH);
}
void send_save(bool tx_bit){
	send_bit(tx_bit);
	++position;
	if(position >= 4){
		send_bit(1);
		position = 0;
	}
}
void connect(){
	send_bit(1);
	for(uint8_t n = 0; n < 5; ++n){
		send_bit(0);
	}
	position = 0;
}
void send_char(char character){
	bool tmp_data = false;
	uint8_t	tmp_bit	= 0;
	send_save(1);
	send_save(0);
	for(uint8_t n = 0; n < 8; ++n){
		tmp_bit = 0b00000001 << (7-n);
		tmp_data = (character & tmp_bit);
		send_save(tmp_data);
	}
}
void send_char_message(const char* value, uint8_t count){
	for(uint8_t n = 0; n < count; ++n){
		send_char(value[n]);
	}
}

void send_int(int32_t number){
	bool tmp_data = false;
	int16_t	tmp_bit	= 0;
	send_save(0);
	send_save(1);
	int16_t tmp_number = number >> 16;
	for(uint8_t n = 0; n < 16; ++n){
		tmp_bit = static_cast < int16_t >(1) << (15-n);
		tmp_data = (tmp_number & tmp_bit);
		send_save(tmp_data);
	}
	for(uint8_t n = 0; n < 16; ++n){
		tmp_bit = static_cast < int16_t >(1) << (15-n);
		tmp_data = (number & tmp_bit);
		send_save(tmp_data);
	}
}

void clear_screen(){
	send_save(0);
	send_save(0);
}