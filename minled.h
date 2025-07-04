#pragma once

struct s_led_properties {

  unsigned int col_rgb;
  unsigned int shutdown_flag;

} typedef s_led_properties;

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

void ledlooptrap(s_led_properties *properties) {

  while(!properties->shutdown_flag) {

    
    
  }
  
}
