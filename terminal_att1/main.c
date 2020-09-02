#include <avr/io.h>
#define BAUD 0x33

//all you need is an arduino for this one, no setup required!


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

int main(void){
    //Continuously send Hello World!
    unsigned char str[30] = "Hello World";
    unsigned char strLength = 13;
    unsigned char i = 0;

    initialize_usart_serial();

    while (1){
        usart_send(str[i++]);
        if (i >= strLength) i = 0;
    }
}