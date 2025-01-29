#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define __AVR_ATmega328P__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

double dutyCycle = 0;

int main(void) {

  DDRD = 0b01000000;

  TTRC0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
  TIMSK0 = (1 << TOIE0)

      OCR0A = (dutyCycle / 100) * 255;

  sei();

  TTR0B = (1 < CS00);

  while (1) {
    _delay_ms(100);
    if (dutyCycle > 100) {
      dutyCycle = 0;
    }
  }
}

ISR(TIMER0_OVF_vect) { OCR0A = (dutyCycle / 100) * 255; }
