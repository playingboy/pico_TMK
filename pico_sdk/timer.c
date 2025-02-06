#include "pico/time.h"

#include "timer.h"

void timer_init(void) {}

void timer_clear(void) {}

uint16_t timer_read(void)
{
    return (uint16_t)to_ms_since_boot(get_absolute_time());
}

uint32_t timer_read32(void)
{
    return to_ms_since_boot(get_absolute_time());
}

uint16_t timer_elapsed(uint16_t last)
{
    return (uint16_t)(timer_read() - last);
}

uint32_t timer_elapsed32(uint32_t last)
{
    return timer_read32() - last;
}
