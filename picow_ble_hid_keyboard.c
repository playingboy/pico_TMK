#include <pico/time.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/util/queue.h"
#include "common/keyboard.h"
#include "common/host.h"

queue_t hid_keyboard_report_queue;

extern void btstack_main();


/* declarations */
uint8_t keyboard_leds(void);
void send_keyboard(report_keyboard_t *report);
void send_mouse(report_mouse_t *report);
void send_system(uint16_t data);
void send_consumer(uint16_t data);

/* host struct */
host_driver_t tmk_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};

int main()
{
    stdio_init_all();

    keyboard_init();
    host_set_driver(&tmk_driver);
    
    if (cyw43_arch_init()) {
        printf("cyw43_init_error\n");
        return 0;
    }

    btstack_main();
    struct
    {
        uint8_t modifier;   /**< Keyboard modifier (KEYBOARD_MODIFIER_* masks). */
        uint8_t reserved;   /**< Reserved for OEM use, always set to 0. */
        uint8_t keycode[6]; /**< Key codes of the currently pressed keys. */
    } hid_keyboard_report_t;

    queue_init_with_spinlock(&hid_keyboard_report_queue, sizeof(hid_keyboard_report_t), 10, spin_lock_claim_unused(true));

    int i = 0;
    while(i<3) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(200);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(200);
        i++;
    }

    while(1) {
        sleep_ms(20);
        keyboard_task();
    }

    return 0;
}
