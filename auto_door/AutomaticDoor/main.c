/*
 * AutomaticDoor.c
 *
 * Created: 2020-09-06 3:00:02 AM
 * Author : Ahmed
 */ 

#include "avr/io.h"

#define BAUD 0x33


void initialize_usart_serial(void){
    //set baud rate to 19200 and init our serial comms
    UCSR0B = (1<<TXEN0);
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
    UBRR0L = BAUD;
}

void usart_send(unsigned char letter){
    //send letter across usart
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = letter;
}

unsigned int capture_period()
{
  	unsigned int t;
  	
    	
    PORTD = 0xFF;	
    TCCR1A = 0;
    TIFR1 = (1<<ICF1);		/* clear input capture flag */
    TCCR1B = 0x41;			/* capture on rising edge */ 
	
  	unsigned char b[20] = "b";
  	unsigned char h[20] = "h"; // op tells us we've reached input
  	
    while ((TIFR1&(1<<ICF1)) == 0);  /* monitor for capture*/
  	
  	usart_send(b[0]);
    t = ICR1;			
    TIFR1 = (1<<ICF1);		/* clear capture flag */

    while ((TIFR1&(1<<ICF1)) == 0);  /* monitor for next rising
                    edge capture */
  	usart_send(h[0]); //we know we've finished capture
	
    t = ICR1 - t;  			/* period= recent capture-
                      previous capture */
  return t;
}


int main (void)
{
	
	DDRD &=!(1<<PD6);
	initialize_usart_serial();
  	unsigned char str[30] = "Hello World";
    unsigned char strLength = 13;
    unsigned char i = 0;
  while(i<13){
    usart_send(str[i++]);
  }

    while (1){
      capture_period();
    }
  
	return 0;
}

