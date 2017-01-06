/* Arduino Code to simulate a JET AFS-1000B Remote
January 6, 2017

I read some posts on the internet that the control board was
based on a Ceramate Technical CP8112B-L8SN24. The board layout
looked very similar to the reference design found in the CP8112B
datasheet. I found that this company also made a remote transmitter
IC (CP8223R).
The remote transmitter used a NEC protocol format and button K01
was defined as the ON/OFF control button. Page 5 had the custom 
code of 0x80. I combine that with the Data Code of 0xC0 and found
that this worked. The other buttons did not follow the custom codes
but instead a custom code of 0x80 was used for all buttons and only
the Data Code changed for each button.

Side note. The control board used a SoNiX SN8P1600 MCU instead of
the Ceramate CP8112B.
*/
#include <IRremote.h>

IRsend irsend;

//uint32_t lower_part = 0xE01F; // SPEED
uint32_t lower_part = 0xD02F; // TIMER
uint32_t codes[0xFF];
bool runXTimes = false; // Set to true if you want to test
uint32_t value = 0;
uint32_t compliment;
int khz = 38; // 38kHz carrier frequency for the NEC protocol

int butONOFF = 4; // Change to pin that will be used
int butSPEED = 5; // Change to pin that will be used
int butTIMER = 6; // Change to pin that will be used

void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); //Used for debugging
  pinMode(butONOFF, INPUT_PULLUP); // ON/OFF no external resistor needed
  pinMode(butSPEED, INPUT_PULLUP); // ON/OFF no external resistor needed
  pinMode(butTIMER, INPUT_PULLUP); // ON/OFF no external resistor needed
}

void loop() {
      if (runXTimes){ // This is only used for testing
        //for (uint32_t value = 0; value < 0xFF; value++) {
        value = 0x80;
        compliment = ~(value) & 0xFF;
        codes[value] = (value << 24) | (compliment << 16) | (lower_part);
        irsend.sendNEC(codes[value], 32);
        Serial.println(codes[value], HEX);
      }
        runXTimes = false;

        if (digitalRead(butONOFF) == LOW)
        {
          irsend.sendNEC(0x807FC03F, 32)
        }
         if (digitalRead(butSPEED) == LOW)
        {
          irsend.sendNEC(0x807FE01F, 32)
        }
         if (digitalRead(butTIMER) == LOW)
        {
          irsend.sendNEC(0x807FD02F, 32)
        }
}
