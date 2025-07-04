#pragma once
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

struct s_led_properties {

  unsigned int data_pin;
  unsigned int col_rgb;
  unsigned int shutdown_flag;

} typedef s_led_properties;

struct s_led_strip_setup {

  unsigned int num_leds;
  
} typedef s_led_strip_setup;

/*
Protocol description: 24 Bits per LED for RGB3C Color+Brightness Information
Then you send that packet x times to set it for x leds.
The order determines which led you target. First packet sets LED1 color info.
The LEDs handle the rest of the comunication.

Packet = 24 Bit.
8 Bit per Color Channel

Encoding:
1 = 0.8us high 0.45us low
0 = 0.4us high 0.85us low
rst = 300us reset sig (use 500 or so with shit cable?)
Most significant bit first


 */

unsigned int props_to_bytes(s_led_properties *properties) {

}

void send_reset_sig() {
  PORTB &= ~(1 << PB4);
  _delay_us(60);
  PORTB |= (1 << PB4);
}

/*void send_single_led(s_led_properties *properties) {
  int* bits = (int*)malloc((size_t)24);
  PORTB &= ~(1 << PB4);
  for(int i = 0; i<24; i++) {
    //bits[i] = (properties->col_rgb & ( 1 << i )) >> i;
    if( ( (properties->col_rgb & ( 1 << i )) >> i) == 1) {
      PORTB |= (1 << PB4);
      _delay_us(0.8);
      PORTB &= ~(1 << PB4);
      _delay_us(0.45);
      } else {
      PORTB |= (1 << PB4);
      _delay_us(0.4);
      PORTB &= ~(1 << PB4);
      _delay_us(0.85);
      }
    //_delay_us(10);
  }
  }*/

void send_single_led(s_led_properties *properties) {
    uint32_t color = properties->col_rgb;
    
    for (int i = 23; i >= 0; i--) {
        if (color & (1UL << i)) {
            PORTB |= (1 << PB4);  // High
            __asm__ __volatile__ (
                "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" 
                "nop\n\t" "nop\n\t"
            );
            PORTB &= ~(1 << PB4); // Low
            __asm__ __volatile__ (
                "nop\n\t" "nop\n\t"
            );
        } else {
            PORTB |= (1 << PB4);  // High
            __asm__ __volatile__ (
                "nop\n\t"
            );
            PORTB &= ~(1 << PB4); // Low
            __asm__ __volatile__ (
                "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" 
                "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"
            );
        }
    }
}

void send_full_strip(s_led_properties* properties, s_led_strip_setup* setup) {
  send_reset_sig();
  for(int i = 0; i < setup->num_leds; i++ ) {
    send_single_led(properties);
  }
}

void ledloop_trap(s_led_properties *properties, s_led_strip_setup* setup) {

  //setp
  DDRB &= ~(1 << PB5);//i
  DDRB |= (1 << PB4);//o
  
  while(!properties->shutdown_flag) {
    send_full_strip(properties,setup);
  }
}
