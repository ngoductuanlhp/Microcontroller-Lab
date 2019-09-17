#include "osc_manager.h"
#include "config.h"

void osc_init() {
    OSCCON = 0b01100111;
    OSCTUNE = 0b00001111;
}
