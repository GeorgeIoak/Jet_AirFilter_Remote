#include <IRremote.h>

IRsend irsend;

//uint32_t lower_part = 0xE01F; // SPEED
uint32_t lower_part = 0xD02F; // TIMER
uint32_t codes[0xFF];
bool runXTimes = true;
uint32_t value = 0;
uint32_t compliment;
int khz = 38; // 38kHz carrier frequency for the NEC protocol

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
      if (runXTimes){
        //for (uint32_t value = 0; value < 0xFF; value++) {
        value = 0x80;
        compliment = ~(value) & 0xFF;
        codes[value] = (value << 24) | (compliment << 16) | (lower_part);
        irsend.sendNEC(codes[value], 32);
        Serial.println(codes[value], HEX);
      }
        runXTimes = false;
}
