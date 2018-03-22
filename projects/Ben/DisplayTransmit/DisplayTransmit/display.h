/* 
* display.h
*
* Created: 22.03.2018 13:07:34
* Author: bmuch
*/
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdint.h>

void GPIO_Init();
void connect();
void send_int(int32_t number);
void clear_screen();
void send_char_message(const char* value, uint8_t count);

#endif //__DISPLAY_H__
