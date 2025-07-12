#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN     PB4    
#define NUM_LEDS    2

// Color format: GRB
#define GREEN 250
#define RED   0
#define BLUE  0

void sendByte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & 0x80) {
            // Send '1'
            PORTB |= (1 << LED_PIN);
            __asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"::);
            PORTB &= ~(1 << LED_PIN);
            __asm__ __volatile__("nop\n\t""nop\n\t"::);
        } else {
            // Send '0'
            PORTB |= (1 << LED_PIN);
            __asm__ __volatile__("nop\n\t""nop\n\t"::);
            PORTB &= ~(1 << LED_PIN);
            __asm__ __volatile__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"::);
        }
        byte <<= 1;
    }
}

void sendColor(uint8_t g, uint8_t r, uint8_t b) {
  sendByte(r);
  sendByte(g);
  sendByte(b);
}

void sendReset() {
    _delay_us(50);
}

int newledtrap(void) {
    DDRB |= (1 << LED_PIN);
    while (1) {
        for (uint16_t i = 0; i < NUM_LEDS; i++) {
            sendColor(GREEN, RED, BLUE);
        }
        sendReset();
        _delay_ms(1000); 
    }
}
