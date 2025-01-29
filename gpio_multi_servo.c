#include <stdint.h>
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define __AVR_ATmega328P__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Define the servo pulse width for 0 and 180 degrees
// Timing works for Adeept AD002. These are the number of ticks
// corresponding to the Pulse Width in ms with a prescaler of 8.
#define SERVO_MIN_PULSE_WIDTH 900  // 2e6 * 0.5 ms
#define SERVO_MAX_PULSE_WIDTH 5000 // 2e6 * 2.5 m

uint16_t calculate_ticks_from_angle(uint16_t angle) {
  return SERVO_MIN_PULSE_WIDTH +
         (uint16_t)((angle / 180.0) *
                    (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH));
}

void timer0_init() {
  // Configure Timer0 in Fast PWM mode (8-bit)
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) |
           (1 << WGM01); // Fast PWM, non-inverting mode
  TCCR0B = (1 << CS01);  // No prescaling
}

void timer1_init() {
  // Configure Timer1 in Fast PWM mode (16-bit)
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) |
           (1 << WGM11);               // Fast PWM, non-inverting mode
  TCCR1B = (1 << WGM12) | (1 << CS11); // No prescaling
}

void timer2_init() {
  // Configure Timer2 in Fast PWM mode (8-bit)
  TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM00) |
           (1 << WGM01); // Fast PWM, non-inverting mode
  TCCR2B = (1 << CS01);  // No prescaling
}

void servo_1(uint16_t angle) { OCR0A = calculate_ticks_from_angle(angle); }

void servo_2(uint16_t angle) { OCR0B = calculate_ticks_from_angle(angle); }

void servo_3(uint16_t angle) { OCR1A = calculate_ticks_from_angle(angle); }

void servo_4(uint16_t angle) { OCR1B = calculate_ticks_from_angle(angle); }

void servo_5(uint16_t angle) { OCR2A = calculate_ticks_from_angle(angle); }

void servo_6(uint16_t angle) { OCR2B = calculate_ticks_from_angle(angle); }

int main() {
  // Initialize the servo
  timer0_init();
  timer1_init();
  timer2_init();

  sei();

  while (1) {
    servo_1(0);
    servo_2(0);
    servo_3(0);
    servo_4(0);
    servo_5(0);
    servo_6(0);
    _delay_ms(1000);

    servo_1(180);
    servo_2(180);
    servo_3(180);
    servo_4(180);
    servo_5(180);
    servo_6(180);
    _delay_ms(1000);
  }

  return 0;
}
