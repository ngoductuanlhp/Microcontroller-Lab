#include "interrupt_manager.h"
#include "config.h"

void interrupt_init() {
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
}

void __interrupt() myISR(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = counter_low;
        TMR0H = counter_high;
        //ledValue++;
        handleButton();
    }
}
