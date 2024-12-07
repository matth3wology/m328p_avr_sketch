#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define __AVR_ATmega328P__

#include <avr/io.h>
#include <util/delay.h>

#define LED 5
#define INPUT 4
#define LSHIFT(x) (1 << x) // Shift bits left by x

int main(void) {

  DDRB = 0b00100000; // Set PB5 pin to out

  PORTB &= LSHIFT(LED); // Turn off the LED

  while (1) {
    if ((PINB & LSHIFT(INPUT)) == (LSHIFT(INPUT))) {
      PORTB |= (LSHIFT(LED)); // Turn the LED on
    } else {
      PORTB &= ~(LSHIFT(LED)); // Turn the LED off
    }
  }
}
