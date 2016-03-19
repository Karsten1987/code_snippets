/*
 * main.c
 *
 *  Created on: Jun 14, 2015
 *      Author: karsten
 */


/* Alle Zeichen zwischen Schrägstrich-Stern
   und Stern-Schrägstrich sind Kommentare */

// Zeilenkommentare sind ebenfalls möglich
// alle auf die beiden Schrägstriche folgenden
// Zeichen einer Zeile sind Kommentar

#include <avr/io.h>          // (1)

int main (void) {            // (2)

   DDRB  = 0xFF;             // (3)
   PORTB = (1<<PB1) | (1<<PB2);             // (4)

   while(1) {                // (5)
     /* "leere" Schleife*/   // (6)
   }                         // (7)

   /* wird nie erreicht */
   return 0;                 // (8)
}
