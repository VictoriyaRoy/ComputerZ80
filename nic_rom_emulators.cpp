
#include <Arduino.h>
#include <stdio.h>

int program[] = {0x06, 0x62, 0x0E, 0x00, 0x21, 0x10, 0x00, 0x7E, 0xED, 0x79, 0x23, 0x0C, 0x10, 0xF9, 0x18, 0xF0,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x45, 0x00,
                 0x00, 0x54, 0xe5, 0xe6, 0x40, 0x00, 0x40, 0x01, 0x56, 0xc0, 0x7f, 0x00, 0x00, 0x01, 0x7f, 0x00,
                 0x00, 0x01, 0x08, 0x00, 0x4f, 0x99, 0x83, 0x46, 0x00, 0x00, 0xa3, 0x66, 0xe1, 0x61, 0x00, 0x00,
                 0x00, 0x00, 0x1f, 0xc6, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                 0x26, 0x27};

// pins initialization
const int iorq = 4;
const int clock = A0;
const int dataBus[] = {31, 33, 35, 37, 39, 41, 43, 45};
const int dataWidth = 8;
const int adressBus[] = {22, 24, 26, 28, 30, 32, 34};
const int adressWidth = 7;
const int oe = 2;
const int cs = 3;

// memory range for network
const int nicStartAdress = 0;
int offset = 0;

// frame buffer
const int bufferCapacity = 98;
int bufferSize = 0;
char frameBuffer[bufferCapacity];

void setup() {
  Serial.begin(9600);
  pinMode(iorq, INPUT);
  pinMode(clock, OUTPUT);
  for (int i = 0; i < dataWidth; i++) {
    pinMode(dataBus[i], INPUT);
  }
  for (int i = 0; i < adressWidth; i++) {
    pinMode(adressBus[i], INPUT);
  }
  pinMode(oe, INPUT_PULLUP);
  pinMode(cs, INPUT_PULLUP);
}

int convertToDecimal(const int pins[], int n) {
  int num = 0, power = 1;
  for (int i = 0; i < n; i++) {
    num += digitalRead(pins[i]) * power;
    power *= 2;
  }
  return num;
}

char str[64];
void printAllBuses() {
  int oe_cs = (digitalRead(2) << 1) | (digitalRead(3));
  if(!oe_cs){
      int dataBusDecimal = convertToDecimal(dataBus, dataWidth);
      sprintf(str, "D: %x \t", dataBusDecimal);
      Serial.print(str);

      int adressBusDecimal = convertToDecimal(adressBus, adressWidth);
      sprintf(str, "A: %d", adressBusDecimal);
      Serial.println(str);
  }
}

void setDataBus(int command) {
  for (int i = 0; i < dataWidth; i++) {
    int bit = command % 2;
    digitalWrite(dataBus[i], bit);
    command /= 2;
  }
}

void configureDataBus() {
  if (digitalRead(oe) | digitalRead(cs))
    for (int i = 0; i < dataWidth; i++)
      pinMode(dataBus[i], INPUT);
  else 
    for (int i = 0; i < dataWidth; i++)
      pinMode(dataBus[i], OUTPUT);
}

int isNicIoRequest() {
  int currentAdress = convertToDecimal(adressBus, adressWidth);
  if (!digitalRead(iorq) && currentAdress == nicStartAdress + offset) {
    Serial.print("NIC request ");
    Serial.println(currentAdress);
    offset++;
    return 1;
  }
  return 0;
}

void addToBuffer() {
  int chunk = 0;
  for (int i = 0; i < dataWidth; i++) 
    chunk |= digitalRead(dataBus[i]) << i;
  frameBuffer[bufferSize] = chunk;
  bufferSize++;
}

void loop() {
  digitalWrite(clock, !digitalRead(clock));

  if (!isNicIoRequest()) {
    int instructionIdx = convertToDecimal(adressBus, adressWidth);
    int command = program[instructionIdx];
    setDataBus(command);
    configureDataBus();
  } else {
    addToBuffer();
    if (bufferSize == bufferCapacity) {
      // send packet to serial
      Serial.write(frameBuffer, sizeof(frameBuffer));
      bufferSize = 0;
      offset = 0;
    }
  }
}