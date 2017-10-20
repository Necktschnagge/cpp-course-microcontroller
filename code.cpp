
int main(void)
{
	/* Replace with your application code */
	DDRC = 1;
	DDRB |= 0b00100000;
	int zeiten[] {1000, 2000,1000,800,600,300,100,500};
	while (1)
	{
		PORTC = 1;
		PORTB |= 0b100000;
		_delay_ms(1000);
		PORTC = 0;
		PORTB &= 0b11011111;
		_delay_ms(500);
		blink(zeiten,8);
		
	}
}