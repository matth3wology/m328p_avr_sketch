#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define __AVR_ATmega328P__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Define the servo pulse width for 0 and 180 degrees
// TODO: Need to fix the timing here
#define SERVO_MIN_PULSE_WIDTH 900  // 2e6 * 0.5 ms
#define SERVO_MAX_PULSE_WIDTH 5000 // 2e6 * 2.5 ms

// Function to initialize Timer1 for PWM
void servo_init() {
  // Set PB1/OC1A as output
  DDRB |= (1 << PB1);

  // Configure Timer1 for Fast PWM mode (ICR1 as TOP)
  TCCR1A =
      (1 << COM1A1) | (1 << WGM11); // Non-inverting mode, WGM11 for Fast PWM
  TCCR1B = (1 << WGM13) | (1 << WGM12) |
           (1 << CS11); // WGM13 and WGM12 for Fast PWM, Prescaler = 8

  // Set TOP value for 50 Hz (20 ms period)
  ICR1 = 39999; // (16 MHz / (8 * 50)) - 1
}

// Function to set the servo angle
void servo_set_angle(uint16_t angle) {
  // Calculate the pulse width based on the angle
  uint16_t pulse_width = SERVO_MIN_PULSE_WIDTH +
                         (uint16_t)((angle / 180.0) * (SERVO_MAX_PULSE_WIDTH -
                                                       SERVO_MIN_PULSE_WIDTH));

  // Set the pulse width (OCR1A value)
  OCR1A = pulse_width; // Scale to timer ticks
}

int main() {
  // Initialize the servo
  servo_init();

  sei();

  while (1) {
    servo_set_angle(0);
    _delay_ms(1000);

    servo_set_angle(180);
    _delay_ms(1000);
  }

  return 0;
}
