#include "timer0_manager.h"
#include "mcc.h"
#include <math.h>

void preCalculate() {
    T0CON = 0b11000111;
    int count = TIME_INTERRUPT_MS * 2 * pow(10,3);
    int count_scaled = count / 256;
    if(count_scaled < 256) {
        counter_low = 255 - count_scaled;
    } else {
        T0CONbits.T08BIT = 0;
        unsigned int temp = 65535 - count_scaled;
        counter_low = (unsigned short int)temp;
        counter_high = (unsigned short int)(temp >> 8);
    }
}

void timer0_init() {
    preCalculate();
    TMR0L = counter_low;
    TMR0H = counter_high;
}



