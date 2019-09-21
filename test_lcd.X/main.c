/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 21, 2019, 9:39 AM
 */


#include <xc.h>
#include "SPI_LCD.h"

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



void pin_init() {
    TRISD = 0x00;
    LATD = 0x00;
    //Asyn EUSART
    //TRISCbits.TRISC7 = 1;
    //TRISCbits.TRISC6 = 0;
//    TRISCbits.RC6 = 1;
//    TRISCbits.RC7 = 1;
//    TRISAbits.TRISA5 = 1;
//    TRISBbits.TRISB0 = 1;
    LATA = 0x00;
    TRISA = 0xF3;
//    ANSELA = 0x0B;

    LATB = 0x00;
    TRISB = 0xFF;
//    ANSELB = 0x3E;
//    WPUB = 0x00;

    LATC = 0x00;
    TRISC = 0xD7;
    ADCON1 = 0b00001111; //DON'T KNOW WHY BUT IT WORKS
}

void main(void) {
    OSCCON = 0b01110111;
    OSCTUNE = 0b00001111;
    pin_init();
    mOPEN_LCD;
    LCDPrint(1, 5, "abc");
    while(1) {
        
    }
    return;
}
