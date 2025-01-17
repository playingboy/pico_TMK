 #include "keyboard.pio.h"
#include "keyboard.h"
#include "hardware/clocks.h"
#include "stdio.h"
#include "pico/stdlib.h"


static uint8_t key_value=0;

static const PIO keyboard_pio=pio1;
static const uint keyboard_sm=0;
static const uint8_t keys[4][4]={
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
    };

static void keyboard_handle() {
    if (pio_interrupt_get(keyboard_pio, 0)) {
        key_value=0;
        pio_interrupt_clear(keyboard_pio, 0);
        uint32_t x, y;
        y=pio_sm_get_blocking(keyboard_pio, keyboard_sm);
        x=pio_sm_get_blocking(keyboard_pio, keyboard_sm);

        for(uint8_t i = 0 ; i < 4; i++){
            if ((x >> i)==1) {x=i;break;}
        }
        for(uint8_t j = 0 ; j < 4; j++){
            if ((y >> j)==1) {y=j;break;}
        }
        key_value = keys[x][y];
    }
}

static void keyboard_pio_init(PIO pio, uint sm, uint set_base, uint in_base, uint freq) {
    uint offset=0;
    pio_sm_config c;
    offset = pio_add_program(pio, &keyboard_program);
    c = keyboard_program_get_default_config(offset);
    
    for (int i=0; i < 4; i++) pio_gpio_init(pio, in_base+i);
    for (int i=0; i < 4; i++) pio_gpio_init(pio, set_base+i);

    pio_sm_set_consecutive_pindirs(pio, sm, in_base, 4, false);
    pio_sm_set_consecutive_pindirs(pio, sm, set_base, 4, true);

    sm_config_set_in_pins(&c, in_base);
    sm_config_set_set_pins(&c, set_base, 4);
   
    sm_config_set_in_shift(&c, false, false, 32);

    float div = clock_get_hz(clk_sys)/freq;
    sm_config_set_clkdiv(&c, div);

    uint pio_irq = pio_get_index(pio)? PIO1_IRQ_0:PIO0_IRQ_0;
    pio_set_irq0_source_enabled(pio, pis_interrupt0, true);
    irq_add_shared_handler(pio_irq, keyboard_handle, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
    irq_set_enabled(pio_irq, true);

    pio_sm_init(pio, sm, offset, &c);

    pio_sm_set_enabled(pio, sm, true);
}
uint8_t get_new_keyboard_value() {
    uint8_t ret_vale = key_value;
    key_value=0;
    return ret_vale;
}
void keyboard_init() {
    keyboard_pio_init(keyboard_pio, keyboard_sm,  8, 12, 2000);
}