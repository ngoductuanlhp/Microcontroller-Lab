
#include "osc_manager.h"
#include "config.h"

void osc_init() {
    OSCCON = 0x70;
    //OSCTUNE = 0b00001111;
}
