#include "config.h"
#include "pin_manager.h"

void pin_init() {
    TRISD = 0x00;
    LATD = 0x00;
    
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0b00001111; //DON'T KNOW WHY BUT IT WORKS
}
