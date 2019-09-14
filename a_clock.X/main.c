/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 14, 2019, 1:27 PM
 */

#include "config.h"

enum State_Button{INIT, PRESSED, PRESSED_1S};
enum State_Button state_buttonRA5, state_buttonRB0;


void interrupt_init() {
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
}

void timer0_init() {
    T0CON = 0b11000111;
    TMR0L = 177;
}

void pin_init() {
    LATA = 0x00;
    TRISA = 0xF3;
//    ANSELA = 0x0B;

    LATB = 0x00;
    TRISB = 0xFF;
//    ANSELB = 0x3E;
//    WPUB = 0x00;

    LATC = 0x00;
    TRISC = 0xD7;
//    ANSELC = 0x04;

    LATD = 0x00;
    TRISD = 0xFF;
//    ANSELD = 0xFF;

    LATE = 0x00;
    TRISE = 0x07;
//    ANSELE = 0x07;

    INTCON2bits.nRBPU = 0x01;
//    TRISD = 0x00;
//    LATD = 0x00;
//    
//    TRISAbits.TRISA5 = 1;
//    TRISBbits.TRISB0 = 1;
//    ADCON1 = 0b00001111; //DON'T KNOW WHY BUT IT WORKS
}

void osc_init() {
    OSCCON = 0b01110111;
    OSCTUNE = 0b00001111;
}

void readButtonRA5() {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if(secondReadRA5 == firstReadRA5) {
        switch(state_buttonRA5) {
            case INIT:
                if(secondReadRA5 == pressed) {
                    checkRA5 = 1;
                    state_buttonRA5 = PRESSED;
                    countRA5++;
                }
                break;
            case PRESSED:
                if(secondReadRA5 != pressed) {
                    countRA5 = 0;
                    state_buttonRA5 = INIT;
                }
                else {
                    countRA5++;
                    if(countRA5 > 99 && countRA5 % 20 == 0) {
                        checkRA5 = 1;
                    }
                }
                break;
        }
    }
}

void __interrupt() myISR(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = 177;
        timerflag_10ms = 1;
        count++;
        if(count >= 100) {
            timerflag_1s = 1;
            count = 0;
        }
        readButtonRA5();
    }
}

void main(void) {  
    pin_init();
    timer0_init();
    interrupt_init();
    osc_init();
    state = CLOCK;
    while(1) {
        switch(state) {
            case CLOCK: clock();
                break;
            case MODIFY: clock();
                break;
            case STOP_WATCH:
                break;
        }
    }
    return;
}
