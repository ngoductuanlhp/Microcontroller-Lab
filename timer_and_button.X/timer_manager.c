#include "timer_manager.h"
#include "config.h"


void preCalculate() {
    T0CON = 0b11100111;
    int count = TIME_INTERRUPT_MS * 2 * pow(10,3);
    int count_scaled = count / 256;
    if(count_scaled < 256) {
        counter_low = 255 - count_scaled;
    } else {
        T0CONbits.T08BIT = 0;
        int temp = 65535 - count_scaled;
        counter_low = temp % 256;
        counter_high = (temp - counter_low) / 256;
    }
}

void timer0_init() {
    preCalculate();
    TMR0L = counter_low;
    TMR0H = counter_high;
}

