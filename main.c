#include "uart_console.h"
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
#include "uart_console.h"

int main() {
  //uart_trap();
  s_led_properties properties;
  properties.col_rgb = 0;
  properties.col_rgb = ~0;
  properties.data_pin = 12;
  s_led_strip_setup setup;
  setup.num_leds = 5;
  
  ledloop_trap(&properties, &setup);
}
