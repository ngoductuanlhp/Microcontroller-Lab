
#include "osc_manager.h"
#include "config.h"

void osc_init() {
    OSCCON = 0b01110111;
    OSCTUNE = 0b00001111;
    //OSCCON = 0x30;
    //OSCTUNE = 0x40;
}
