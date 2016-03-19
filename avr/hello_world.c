/*
M=atmega8; F=${0:0:-2}; rm -f "$F".hex; avr-gcc -mmcu=$M -Os \
-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
-Wall -Wstrict-prototypes -std=gnu99 -g "$F".c -o "$F".elf && \
avr-objcopy -O ihex -R .eeprom "$F".elf "$F".hex && \
avrdude -c usbasp -p $M -B 12 -U flash:w:"$F".hex:i; exit; */

#include <avr/io.h>

int main(void)
{
  DDRB= 0xFF;
  while(1) {
    PORTB= 0x03;
    // ...
    }
  return 0;
}

