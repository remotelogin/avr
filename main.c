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
}
