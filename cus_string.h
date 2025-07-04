#pragma once
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>

struct String {
  char *buf;
  unsigned int max_size;
  unsigned int current_pos;  
} typedef String;

bool init_string(String* tomod, unsigned int new_max_size) {
  tomod->buf = (char *)malloc((size_t)128);
  tomod->max_size = new_max_size;
  tomod->current_pos = 0;
}

bool set(String* tomod, char *new_s, unsigned int new_length) {
  for (unsigned int i = 0; i < tomod->max_size; i++) {
    tomod->buf[i] = new_s[i];
  }
  tomod->buf[tomod->max_size] = '\n';
  tomod->max_size = new_length;
  return true;
}

bool append(String* tomod, char new_c) {
  if (tomod->current_pos + 2 >= tomod->max_size)
    tomod->current_pos = 0;
  tomod->buf[tomod->current_pos] = new_c;
  tomod->buf[tomod->current_pos + 1] = '\0';
  tomod->current_pos++;
  
  return true;
}

bool clear(String* tomod) {
  free(tomod->buf);
  tomod->buf = (char *)malloc((size_t)128);
  tomod->current_pos = 0;
  return true;
}

bool pop(String* tomod) {
  if(tomod->current_pos>1) {
    tomod->buf[tomod->current_pos] = '\0';
  } else
    return false;
  return true;
}
