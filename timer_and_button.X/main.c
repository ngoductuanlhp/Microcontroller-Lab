/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 11, 2019, 1:09 PM
 */

// PIC18F8722 Configuration Bit Settings

// 'C' source line config statements

#include "config.h"

void main(void) {
    pin_init();
    timer0_init();
    interrupt_init();
    osc_init();
    
    while(1) {
        FSM();
    }
}
