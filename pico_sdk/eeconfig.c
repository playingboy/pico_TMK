

#include "eeconfig.h"



/*****************/
/* TMK functions */
/*****************/

void eeconfig_init(void)
{
    return;
}

void eeconfig_enable(void)
{
    return;
}

void eeconfig_disable(void)
{
    return;
}

bool eeconfig_is_enabled(void)
{
    return 1;
}

uint8_t eeconfig_read_debug(void)      { return 0; }
void eeconfig_write_debug(uint8_t val) { return; }

uint8_t eeconfig_read_default_layer(void)      { return 0; }
void eeconfig_write_default_layer(uint8_t val) { return; }

uint8_t eeconfig_read_keymap(void)      { return 0; }
void eeconfig_write_keymap(uint8_t val) { return; }

#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void)      { return eeprom_read_byte(EECONFIG_BACKLIGHT); }
void eeconfig_write_backlight(uint8_t val) { eeprom_write_byte(EECONFIG_BACKLIGHT, val); }
#endif
