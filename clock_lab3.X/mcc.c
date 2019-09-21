#include "mcc.h"

void SYSTEM_Initialize(void)
{
    osc_init();
    pin_init();
    interrupt_init();
    timer0_init();
    mOPEN_LCD;
}
