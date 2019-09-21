#include "interrupt_manager.h"
#include "mcc.h"

unsigned int count1 = 0;

void interrupt_init() {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
}

void __interrupt() myISR(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = counter_low;
        TMR0H = counter_high;
        handleButton();
        count++;
        count1++;
        if(count1 == TIME_INTERVAL_100MS) {
            ms_flag = 1;
            count1 = 0;
        }
        if(count == HIDE_INTERVAL) {
            hide_flag = 1;
        }
        if(count == TIME_INTERVAL_1S) {
            count = 0;
            second_flag = 1;
        }
    }
}

