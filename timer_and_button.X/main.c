/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 11, 2019, 1:09 PM
 */

// PIC18F8722 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#ifdef _18F8722
#pragma config  OSC = INTIO7
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#include <xc.h>
#include <stdio.h>

#define time_pressed1 100
#define time_pressed2 300

#define time_interval1 50
#define time_interval2 10

unsigned char firstReadRA5 = 1;
unsigned char secondReadRA5 = 1;
unsigned char firstReadRB0 = 1;
unsigned char secondReadRB0 = 1;

unsigned char ledValue = 0;

unsigned char buttonRA5 = 0;
unsigned char buttonRA5_1s_pressed = 0;
unsigned char buttonRA5_3s_pressed = 0;

unsigned char buttonRB0 = 0;
unsigned char buttonRB0_1s_pressed = 0;
unsigned char buttonRB0_3s_pressed = 0;

unsigned int countRA5 = 0;
unsigned char increase1 = 0;
unsigned char increase2 = 0;

unsigned int countRB0 = 0;
unsigned char decrease1 = 0;
unsigned char decrease2 = 0;


void interrupt_init() {
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
}

void timer0_init() {
    T0CON = 0b11000111;
    TMR0L = 177;
}

void pin_init() {
    TRISD = 0x00;
    LATD = 0x00;
    
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111; //DON'T KNOW WHY BUT IT WORKS
}

void osc_init() {
    OSCCON = 0b01110111;
    OSCTUNE = 0b00001111;
}

int readButtonRA5() {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if(secondReadRA5 == firstReadRA5) {
        return (secondReadRA5 == 0) ? 2 : 1;
    }
    return 0;
}

int readButtonRB0() {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if(secondReadRB0 == firstReadRB0) {
        return (secondReadRB0 == 0) ? 2 : 1;
    }
    return 0;
}

void handleButton() {
    int checkRA5 = readButtonRA5();
    int checkRB0 = readButtonRB0();
    if(checkRA5 == 2) {
        countRB0 = 0;
        countRA5++;
        if(countRA5 % time_interval2 == 0)
            increase2 = 1;
        if(countRA5 % time_interval1 == 0)
            increase1 = 1;
    }
    else if(checkRB0 == 2) {
        countRA5 = 0;
        countRB0++;
        if(countRB0 % time_interval2 == 0)
            decrease2 = 1;
        if(countRB0 % time_interval1 == 0)
            decrease1 = 1;
    }
    else if(checkRB0 == 1 || checkRA5 == 1) {
        countRA5 = 0;
        countRB0 = 0;
    }
}

void __interrupt() myISR(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = 177;
        handleButton();
        printf("hello");
    }
}

void main(void) {
    enum State{INIT, INCREASE0, INCREASE1, INCREASE2, DECREASE0, DECREASE1, DECREASE2};
    enum State state = INIT;
    pin_init();
    timer0_init();
    interrupt_init();
    osc_init();
    while(1) {
        LATD = ledValue;
        switch(state) {
            case INIT:
                if(countRA5 > 0) {
                    ledValue++;
                    state = INCREASE0;
                }
                else if(countRB0 > 0) {
                    ledValue--;
                    state = DECREASE0;
                }
                break;
            case INCREASE0:
                if(countRA5 > time_pressed1) 
                    state = INCREASE1;
                else if (countRA5 == 0)
                    state = (countRB0 > 0) ? DECREASE0 : INIT;
                break;
            case INCREASE1:
                if(increase1) {
                    ledValue++;
                    increase1 = 0;
                }
                if(countRA5 > time_pressed2)
                    state = INCREASE2;
                else if(countRA5 == 0)
                    state = (countRB0 > 0) ? DECREASE0 : INIT;
                break;
            case INCREASE2:
                if(increase2) {
                    ledValue++;
                    increase2 = 0;
                }
                if(countRA5 == 0)
                    state = (countRB0 > 0) ? DECREASE0 : INIT;
                break;
            case DECREASE0:
                if(countRB0 > time_pressed1)
                    state = DECREASE1;
                else if (countRB0 == 0)
                    state = (countRA5 > 0) ? INCREASE0 : INIT;
                break;
            case DECREASE1:
                if(decrease1) {
                    ledValue--;
                    decrease1 = 0;
                }
                if(countRB0 > time_pressed2)
                    state = DECREASE2;
                else if(countRB0 == 0)
                    state = (countRA5 > 0) ? INCREASE0 : INIT;
                break;
            case DECREASE2:
                if(decrease2) {
                    ledValue--;
                    decrease2 = 0;
                }
                if(countRB0 == 0)
                    state = (countRA5 > 0) ? INCREASE0 : INIT;
                break;
        }
    }
}
