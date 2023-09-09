#include <avr/io.h>

#define RED_VISIBLE_TIME 8000
#define YELLOW_VISIBLE_TIME 3000
#define GREEN_VISIBLE_TIME 10000
#define PWM_ON_TIME 3
#define PWM_OFF_TIME 5

#include <util/delay.h>

const uint8_t RED_BITS = 0B00010000;
const uint8_t YELLOW_BITS = 0B00100000;
const uint8_t GREEN_BITS = 0B01000000;
const uint8_t ALL_BITS = RED_BITS | YELLOW_BITS | GREEN_BITS;



void light_on_off(uint8_t bits, uint16_t visible_time_ms) {
  uint16_t period = visible_time_ms / (PWM_ON_TIME + PWM_OFF_TIME);

  for(uint16_t i = 0; i < period; i++) {
    // ON
    PORTA |= bits;
    /* _delay_ms(visible_time_ms); */
    _delay_ms(PWM_ON_TIME);
    // OFF
    PORTA &= ~ ALL_BITS;
    _delay_ms(PWM_OFF_TIME);
  }
}


int main (void)
{
  // Use Port A4,5,6 for red, yellow, green
  DDRA |= 0B01110000;

  while(1) {
    light_on_off(GREEN_BITS, GREEN_VISIBLE_TIME);

    light_on_off(YELLOW_BITS, YELLOW_VISIBLE_TIME);

    light_on_off(RED_BITS, RED_VISIBLE_TIME);

  }
}
