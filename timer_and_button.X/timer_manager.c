#include "timer_manager.h"
#include "config.h"

void timer0_init() {
    T0CON = 0b11000111;
    TMR0L = 177;
}
