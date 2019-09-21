#include "mcc.h"
#include "pin_manager.h"

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
