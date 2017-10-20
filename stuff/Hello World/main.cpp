#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()


class Blinker {
private:
    unsigned int ms_on_time;
    unsigned int ms_off_time;
public:
    Blinker(unsigned int ms_on_time, unsigned int ms_off_time) : ms_on_time(ms_on_time), ms_off_time(ms_off_time) {
        DDRC = 0x01;
    }

    void operator()(unsigned int how_often){ // What is wrong here? Or what is "just" not pretty?
        PORTC = 0b00000001;
        _delay_ms(ms_on_time);
        PORTC = 0b00000000;
        _delay_ms(ms_off_time);
    }
};


int main(){
    Blinker blinker{500,500};
    while(true)
    {
        blinker(5);
        _delay_ms(3000);
    }
}
