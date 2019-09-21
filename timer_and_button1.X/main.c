/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 17, 2019, 4:16 PM
 */
#include "config.h"
#include "SPI_LCD.h"

void main(void) {
    pin_init();
    timer0_init();
    interrupt_init();
    osc_init();
    eusart_init();
    mOPEN_LCD;
    while(1) {
        FSM();
    }
}
