#define F_CPU 16000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "f_macros.h"


void GPIO_init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000110;
}

namespace clock {
	using Time = uint64_t;
	
	constexpr Time ZEROTime {0};
	constexpr Time INFINITYTime {0xFFFFFFFFFFFFFFFF};
	constexpr Time ONESecond {15625};
	static_assert(ONESecond * 1024uLL == 16000000uLL,"ONESecond: something went wrong.");
	
	uint64_t counter; // ! every access to counter is ISR critical.
	
	void init(){
		counter = 0;
		cli(); // deactivate global interrupts
		TCCR0A = 0x00; // ~ NO PWM
		TCNT0 = 0; // counter starts at zero
	
		TIMSK0 = 0b00000001; // activate Overflow Interrupt

		TCCR0B = 0b00000101; // CTC (Clear Timer on Compare Match) (bit 3)
		// start timer running from system clock with prescaler 1024 (bit 2:0)
	
		sei();	// activate global interrupts
	}
	
	Time get_time(){
		macro_interrupt_critical(
			return (counter << 8) + TCNT0;
		);
	}
}

	/* interrupt subroutine */
ISR (__vector_TIMER0_OVF){
	++clock::counter;
}



class Blinker {
	using Time = clock::Time;

	Time on_time{clock::ONESecond};
	Time off_time{clock::ONESecond};
	
	uint64_t blinks_left_doubled;
	
	Time swap_timeout;
	
	inline void led_off(){PORTD &= 0b11111110;}
	inline void led_on(){PORTD |= 0b00000001;}
	
public:
	Blinker(): blinks_left_doubled(0), swap_timeout(clock::INFINITYTime) {}
	
	void set(Time on_time, Time off_time, uint32_t blinks = 1){
		this->on_time = on_time;
		this->off_time = off_time;
		this->blinks_left_doubled = 2 * blinks;
		swap_timeout = clock::ZEROTime;
	}
	
	void stop(){
		led_off();
		blinks_left_doubled = 0;
		swap_timeout = clock::INFINITYTime;
	}
	
	void run(Time now){
		if (blinks_left_doubled != 0){
			if (now > swap_timeout){
				if (blinks_left_doubled % 2){
					swap_timeout = now + off_time;
					led_off();		
				} else {
					swap_timeout = now + on_time;
					led_on();
				}
				--blinks_left_doubled;
			}
		}
	}
	
	inline bool is_finished(){ return blinks_left_doubled == 0; }
		
};

class Preller {
	using Time = clock::Time;
	
	static constexpr Time IGNORETime {3 * clock::ONESecond / 100}; // 30ms
	
	bool pin_old;
	bool pin_new;
	
	Time ignore_until;
	
public:
	Preller(bool initial_pin) : pin_old(initial_pin), pin_new(initial_pin), ignore_until(clock::ZEROTime){}
	
	inline void latch(){ pin_old = pin_new; }
	
	void operator()(Time now, bool input){
		latch();
		if (now > ignore_until){
			pin_new = input;
			if (pin_new != input) ignore_until = now + IGNORETime;
		}
	}
	
	inline bool value(){ return pin_old; }
	inline bool v(){ return pin_old; }
		
	inline bool	new_value(){ return pin_new; }
	inline bool nv(){ return pin_new; }
		
};



int main(void)
{
	GPIO_init();
	clock::init();

	uint16_t counter {0};
	
	Blinker blinker;
	blinker.set(clock::ONESecond / 10, clock::ONESecond / 10, 20);

	Preller c_preller(1); // for counter pin;
	Preller p_preller(1); // for printer pin / output pin;
	
	clock::Time reached_reset{ clock::INFINITYTime};
	
	bool do_not_print {false};
	
	
	while (true){ // central control loop
		
		// neue entprellte inputs pollen:
		c_preller(clock::get_time(),PIND & 0b010);
		p_preller(clock::get_time(),PIND & 0b100);
		
		if ((!c_preller.value())&&(c_preller.new_value())){ // rising edge on counter button // release counter button
			++counter;
		}
		
		if (p_preller.value() && (!p_preller.new_value())){ // falling edge on print button // press print button
			reached_reset = clock::get_time() + 2 * clock::ONESecond;
		}
		
		if ((!p_preller.new_value()) && (clock::get_time() > reached_reset)){ // print button is pressed for longer than 2s
			counter = 0;
			blinker.stop();
			blinker.set(clock::ONESecond / 10, clock::ONESecond / 10, 20);
			reached_reset = clock::INFINITYTime;
			do_not_print = true;
		}
		
		if ((!p_preller.value())&& p_preller.new_value()){ // print button is released
			if (!do_not_print){ // if this was rather a reset than a print then do not print
				if (blinker.is_finished()){
					blinker.set(clock::ONESecond / 2, clock::ONESecond / 2, counter);
				}
			}
			do_not_print = false;
		}
		
		blinker.run(clock::get_time());
		c_preller.latch();
		p_preller.latch();
		
	}
}