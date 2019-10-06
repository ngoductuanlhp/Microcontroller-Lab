/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on October 5, 2019, 9:58 PM
 */
// PRAGMA
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

#include "mcc.h"

int LED_state[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void blink_LED0() {
    LED_state[0] = !LED_state[0];
    LATDbits.LATD0 = LED_state[0];
}

void blink_LED1() {
    LED_state[1] = !LED_state[1];
    LATDbits.LATD1 = LED_state[1];
}

void blink_LED2() {
    LED_state[2] = !LED_state[2];
    LATDbits.LATD2 = LED_state[2];
}
void blink_LED3() {
    LED_state[3] = !LED_state[3];
    LATDbits.LATD3 = LED_state[3];
}
void blink_LED4() {
    LED_state[4] = !LED_state[4];
    LATDbits.LATD4 = LED_state[4];
}
void blink_LED5() {
    LED_state[5] = !LED_state[5];
    LATDbits.LATD5 = LED_state[5];
}

void blink_LED(void* data) {
    char idx = (char)data;
    LED_state[idx] = !LED_state[idx];
    switch(idx) {
        case 0: LATDbits.LATD0 = LED_state[idx];
            break;
        case 1: LATDbits.LATD1 = LED_state[idx];
            break;
        case 2: LATDbits.LATD2 = LED_state[idx];
            break;
        case 3: LATDbits.LATD3 = LED_state[idx];
            break;
        case 4: LATDbits.LATD4 = LED_state[idx];
            break;
        case 5: LATDbits.LATD5 = LED_state[idx];
            break;
        case 6: LATDbits.LATD6 = LED_state[idx];
            break;
        case 7: LATDbits.LATD7 = LED_state[idx];
            break;
    }
}

void main(void) {
    system_initialize();
    char idx0 = register_timer(1000, 0, blink_LED, 0);
    char idx1 = register_timer(1000, 200, blink_LED, 1);
    char idx2 = register_timer(3000, 400, blink_LED, 2);
    char idx3 = register_timer(9000, 400, blink_LED, 3);
    char idx4 = register_timer(5500, 400, blink_LED, 4);
    char idx5 = register_timer(3000, 400, blink_LED, 5);
    char idx6 = register_timer(2000, 400, blink_LED, 6);
    char idx7 = register_timer(2000, 400, blink_LED, 7);

    while(1) {
        dispatch();
        //LATD = value;
    }
    return;
}