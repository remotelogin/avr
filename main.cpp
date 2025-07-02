#include <avr/io.h>
#include <util/delay.h>

int main() {
  DDRB &= ~(1 << PB5); 
  DDRB |= (1 << PB4);
  while (1) {
    if(PINB & (1 << PB4)){
      PORTB = PORTB ^ (1 << PB5);
    }
    else {
      PORTB = PORTB ^ ~(1 << PB5);
    }
    _delay_ms(5);
  }
}
