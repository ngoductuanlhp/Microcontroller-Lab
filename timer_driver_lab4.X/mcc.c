#include "mcc.h"

void osc_initialize(void) {
    OSCCON = 0x70;
}

void pin_initialize(void) {
    LATC = 0x00;
    TRISC = 0xD7;
    ADCON1 = 0b00001111;
    
    //LED
    LATD = 0x00;
    TRISD = 0x00;
    
    LATA = 0x00;
    TRISA = 0xF3;
//    ANSELA = 0x0B;

    LATB = 0x00;
    TRISB = 0xFF;

}

void interrupt_initialize(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void system_initialize(void) {
    osc_initialize();
    pin_initialize();
    interrupt_initialize();
    start_timer(0);
    start_timer(1);
}
