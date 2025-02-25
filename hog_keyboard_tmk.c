#include "hog_keyboard_tmk.h"
#include "pico/time.h"
#include <ble/gatt-service/hids_device.h>
#include <btstack_ring_buffer.h>
#include <stdint.h>
#include "common/report.h"


uint16_t keyboard_led_stats __attribute__((aligned(2))) = 0;

extern queue_t hid_keyboard_report_queue;
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
  struct
    {
        uint8_t modifier;   /**< Keyboard modifier (KEYBOARD_MODIFIER_* masks). */
        uint8_t reserved;   /**< Reserved for OEM use, always set to 0. */
        uint8_t keycode[6]; /**< Key codes of the currently pressed keys. */
    } hid_keyboard_report_t;
  hid_keyboard_report_t.modifier = report->mods;
  for (int i = 0; i < 6; i++) {
    hid_keyboard_report_t.keycode[i] = report->keys[i];
  }
  hid_keyboard_report_t.reserved = report->reserved;

  queue_try_add(&hid_keyboard_report_queue, &hid_keyboard_report_t);
  //queue_try_add(&hid_keyboard_report_queue, report);
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
