/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 17, 2019, 4:16 PM
 */
#include "config.h"

void main(void) {
    pin_init();
    timer0_init();
    interrupt_init();
    osc_init();
    
    while(1) {
        FSM();
    }
    return;
}
