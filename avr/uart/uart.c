/*
 * uart.c
 *
 *  Created on: Jun 14, 2015
 *      Author: karsten
 */

/* apply correct fuses based on here
 * http://www.engbedded.com/fusecalc/
 * can be set via avrdude
 * e.g. avrdude -c stk500 -P /dev/ttyUSB0 -p m8 -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m
 */
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL
#define BAUD 4800UL
#define USART_BAUD_SELECT ((F_CPU+BAUD*8)/(BAUD*16)-1)  // clever runden
#define BAUD_REAL (F_CPU/(16*(USART_BAUD_SELECT+1)))    // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)    // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Baudratenabweichung groesser 1% und damit zu hoch!
#endif

void initUsart(void) {
  UCSRB = (1<<RXEN) | (1<<TXEN);
  UCSRC = (1<<URSEL)|(3<<UCSZ0);

  UBRRH = (USART_BAUD_SELECT >> 8);
  UBRRL = (USART_BAUD_SELECT & 0xFF);
}

void sendChar (char c) {
  while (!(UCSRA & (1<<UDRE))) {}
  UDR = c;
}

unsigned char receiveChar (void) {
  while(!(UCSRA & (1<<RXC))) {}
  return UDR;
}



int main(){

   // Ausgabe von 0123456789
   char c = 'k';

   initUsart();

   while (1) {
    _delay_ms(500);
    sendChar(c);
   }

   return 0; // never reached


}

