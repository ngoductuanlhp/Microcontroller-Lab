#include "mcc.h"

void osc_initialize(void) {
    OSCCON = 0x70; //Fosc = 8MHz
}

void pin_initialize(void) {
    LATC = 0x00;
    TRISC = 0xD7;
    ADCON1 = 0b00001111;
    
    LATA = 0x00;
    TRISA = 0xF3;
//    ANSELA = 0x0B;

    LATB = 0x00;
    TRISB = 0xFF;
    
    //LED
    LATD = 0x00;
    TRISD = 0x00;
}

void PWM_initialize(void) {
    TRISGbits.RG3 = 0; //CCP4
    TRISGbits.RG4 = 0; //CCP5
    PR2 = 249; //period = 2ms
    T2CON = 0x03;//prescale = 16
    CCP4CON = 0b00001100;
    CCPR4L = 0x00;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void interrupt_initialize(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}


void system_initialize(void) {
    osc_initialize();
    pin_initialize();
    interrupt_initialize();
    LTD_initialize();
    mOPEN_LCD;
    start_timer(0);//for timestamp
    start_timer(1);//for handle tasks
}

//void pin_initialize(void) {
//    LATC = 0x00;
//    TRISC = 0xD7;
//    ADCON1 = 0b00001111;
//    
//    //LED
//    LATD = 0x00;
//    TRISD = 0x00;
//    
//    LATA = 0x00;
//    TRISA = 0xF3;
////    ANSELA = 0x0B;
//
//    LATB = 0x00;
//    TRISB = 0xFF;
//
//}
//
//void interrupt_initialize(void) {
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
//}
//
//void system_initialize(void) {
//    osc_initialize();
//    pin_initialize();
//    interrupt_initialize();
//    mOPEN_LCD;
//    start_timer(0);
//    start_timer(1);
//}
//
//void USART_initialize(void) {
//    //EUSART1 mode
//    TRISCbits.RC6= 0;
//    TRISCbits.RC7 = 1;
//    
//    TXSTAbits.BRGH = 1;
//    SPBRG = 51; //Baud_rate = 9600
//    
//    TXSTAbits.SYNC = 0;
//    RCSTAbits.SPEN = 1;
//    
//    TXSTAbits.TXEN = 1;
//    RCSTAbits.CREN = 1;
//    
//    TXSTAbits.TX9 = 0;
//    RCSTAbits.RX9 = 0;
//}


