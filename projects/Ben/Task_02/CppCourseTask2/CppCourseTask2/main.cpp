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

enum class ButtonTypeDef : uint8_t {
	Button1		= 0b010,
	Button2		= 0b100,
	Both		= 0b110,
};
constexpr ButtonTypeDef Button1{ButtonTypeDef::Button1};
constexpr ButtonTypeDef Button2{ButtonTypeDef::Button2};

inline bool is_pressed(ButtonTypeDef button);

void GPIO_Init(); // Nur-Deklaration


int main(void)
{
	uint16_t	counter {0};
	uint16_t	blinker {0};
	uint32_t	timeout {2000};
	
	GPIO_Init();
	
	/* Replace with your application code */
	while (1){
		if(is_pressed(Button1) == true){						// wenn taster gedrückt
			counter++;
			while(is_pressed(Button1) == true){
			}
			_delay_ms(200);
		}
		if(is_pressed(Button2) == true){						// wenn taster gedrückt
			blinker = counter;
			while(is_pressed(Button2) == true){
				_delay_ms(1);
				timeout--;
				if(timeout < 1){
					counter = 0;
					blinker = 20;
					break;
				}
			}
		}
		if (blinker > 0){
			LED_Blink();
			blinker--;
			timeout = 2000;
		} else {
			PORTD &= 0b11111110;
			timeout = 2000;
		}
	}
}

inline bool is_pressed(ButtonTypeDef button){
	return (!(PIND & static_cast<uint8_t>(button)));
}

void GPIO_Init(){
	DDRD |= 0b00000001;
	PORTD |= 0b00000110;
}

void LED_Blink(){
	PORTD |= 0b00000001;
	_delay_ms(250);
	PORTD &= 0b11111110;
	_delay_ms(250);
}

/*
void Timer1_Init()
{
  // Timer 2 konfigurieren
  GTCCR |= (1 << TSM) | (1 << PSRASY);  //Timer anhalten, Prescaler Reset
  TCCR1A = (1 << WGM11);                //CTC Modus
  TCCR1B |= (1 << CS22) | (1 << CS21);  //Prescaler 256
  // 32768 / 256 / 1 = 128                Intervall = 1s
  OCR2A = 128 - 1;
  TIMSK2 |= (1<<OCIE2A);                //Enable Compare Interrupt
  GTCCR &= ~(1 << TSM);                 //Timer starten
  sei();                                //Enable global Interrupts
}
*/