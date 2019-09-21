#include "osc_manager.h"
#include "mcc.h"

void osc_init() {
    OSCCON = 0x70; //Internal clock , Freq = 8MHz
    //OSCTUNE = 0b00001111;
    //OSCCON = 0x30;
    //OSCTUNE = 0x40;
}
