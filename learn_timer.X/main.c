// PIC18F8722 Configuration Bit Settings

// 'C' source line config statements

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
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

unsigned char portValue;

void __interrupt() myISR(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        portValue++;
        INTCONbits.TMR0IF = 0;
        TMR0L = 92;
        //TMR0H = 0b00001011;
    }
}

void main(void) {
    TRISD = 0x00;
    LATD = 0x00;
    T0CON = 0b11000011;
    TMR0L = 92;
    //TMR0H = 0b00001011;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    while(1) {
        LATD = portValue;
    }
}
