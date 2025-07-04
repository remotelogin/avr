#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>

#include "minled.h"
#include "cus_string.h"



void uart_init(void) {
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;

#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~(_BV(U2X0));
#endif

  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

char uart_getc() {
  while (!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

int uart_putchar(char c, FILE *stream) {
  if (c == '\n') {
    uart_putchar('\r', stream);
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

int uart_getchar(FILE *stream) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}


void uart_trap() {
  
  FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
  FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
  
  // setup uart
  uart_init();
  stdout = &uart_output;
  stdin = &uart_input;

  char input;

  // setup io
  DDRB &= ~(1 << PB5);
  DDRB |= (1 << PB4);

  String buffer;
  init_string(&buffer,32);

  puts("Controller online.");

  // main loop
  while (1) {

    // check if D12 is high
    if (PINB & (1 << PB4)) {
      PORTB = PORTB ^ (1 << PB5);
    } else {
      PORTB = PORTB ^ ~(1 << PB5);
    }

    // char uh[16];
    // fgets(uh, sizeof(uh), stdin);
    // printf("%s\n", uh);

    char tmp = uart_getc();
    switch(tmp) {
    case '\r': {
      printf("clearing buf\n");
      clear(&buffer);
      break;}
    case '\b': {
      pop(&buffer);
      break;
    }
    default: {
      append(&buffer, tmp);
    }
      
    }

    printf("%s\n", buffer.buf);

    // make cpu not die
    _delay_ms(10);
  }

  
}
