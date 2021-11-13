#include <Arduino.h>

byte data[] = {0x3E, 0x00, 0xD3, 0xFF, 0x06, 0x00, 0x10, 0xFE, 0x2F, 0xD3, 0xFF, 0x10, 0xFE, 0x18, 0xF1};
// byte data[] = {0x3E, 0x01, 0xD3, 0xFF, 0xC3, 0x00, 0x00};
// byte data[] = {0xD3, 0xFF, 0x06, 0x20, 0x10, 0xFE, 0x2F, 0xD3, 0xFF, 0x06, 0x20, 0x10, 0xFE, 0x18, 0xF1};
// byte data[] = {0xD3, 0xFF, 0x06, 0x00, 0x10, 0xFE, 0x10, 0xFE, 0x2F, 0xD3, 0xFF, 0x10, 0xFE, 0x18, 0xF1};

void setup() {
	DDRD = 0x00; // data pins 0-7
	DDRB = 0x00; // address pins 8-11 
	PORTB = 0x30; 
}

void loop() {
	PORTD = data[PINB & 0xF];
	DDRD = PINB & 0x30 ? 0x0 : 0xFF;
}