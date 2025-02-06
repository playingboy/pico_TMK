#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int platform_setup(void){
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("cyw43_arch_init error\n");
        return 0;
    }
    return 1;
}