#include <Arduino.h>
#include <stdio.h>

// Z80 program byte array
byte data[] = {0x3E, 0x00, 0xD3, 0xFF, 0x06, 0x00, 0x10, 0xFE, 0x2F, 0xD3, 0xFF, 0x10, 0xFE, 0x18, 0xF1};

// PORTD - data pins (Arduino pins 0-7)
// PORTB - address pins (Arduino pins 8-11)
// PORTB (4) - OE (Arduino pin 12)
// PORTB (5) - CS (Arduino pin 13)

void setup() {
   Serial.begin(9600);
   DDRD = 0x00; // set PORTD in input mode
   DDRB = 0x00; // set PORTB in input mode
   PORTB = 0x30; // set OE and CS in input pullup mode
   pinMode(A0, OUTPUT);
}

char str[64];
void printAllBuses() {
  int oe_cs = (digitalRead(12) << 1) | (digitalRead(13));
  if(!oe_cs){
      sprintf(str, "OE_CS:%d, CLK:%d, A:%x D:%x",oe_cs, digitalRead(A0), PINB, PORTD);
      Serial.println(str);
  }
}

void loop() {
  delay(100);
  digitalWrite(A0, !digitalRead(A0));
  delay(10);
  printAllBuses();
  PORTD = data[PINB & 0xF]; // write data to PORTD
  DDRD = PINB & 0x30 ? 0x0 : 0xFF; // set mode of PORTD
}
