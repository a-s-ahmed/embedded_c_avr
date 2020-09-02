#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

//Makes LED connected to D2 blink. See png file for arduino layout


int main()
{
  DDRD = DDRD|(1<<PD2); //Set PD2 to Output
  while(1)
  {
   PORTD &=!(1<<PD2); //Set PD2 to low
    _delay_ms(1000);
   PORTD |=(1<<PD2); //Set PD2 to high
    _delay_ms(1000);
  }
}
