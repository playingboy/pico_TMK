#include "hog_keyboard_tmk.h"
#include "pico/time.h"


uint16_t keyboard_led_stats __attribute__((aligned(2))) = 0;
/* ---------------------------------------------------------
 *                  Keyboard functions
 * ---------------------------------------------------------
 */




/* LED status */
uint8_t keyboard_leds(void) {
  return (uint8_t)(keyboard_led_stats & 0xFF);
}

/* prepare and start sending a report IN
 * not callable from ISR or locked state */
void send_keyboard(report_keyboard_t *report) {
  sleep_ms(1);
  (void)report;
  return;
}

/* ---------------------------------------------------------
 *                     Mouse functions
 * ---------------------------------------------------------
 */


void send_mouse(report_mouse_t *report) {
  (void)report;
}
/* ---------------------------------------------------------
 *                   Extrakey functions
 * ---------------------------------------------------------
 */

void send_system(uint16_t data) {
  (void)data;
}
void send_consumer(uint16_t data) {
  (void)data;
}
/* ---------------------------------------------------------
 *                   Console functions
 * ---------------------------------------------------------
 */

int8_t sendchar(uint8_t c) {
  (void)c;
  return 0;
}

void sendchar_pf(void *p, char c) {
  (void)p;
  sendchar((uint8_t)c);
}
