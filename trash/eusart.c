#include "eusart.h"

void eusart_init() {
    INTCONbits.PEIE = 1;
    
    RCSTA = 0x80;//0b1xxxxxxx
    TXSTA = 0x26;//0bx1x0x1xx
    SPBRG = 0x33;
    // TXREG 0; 
    TXREG = 0x00;

    // RCREG 0; 
    RCREG = 0x00;
}


uint8_t EUSART1_Read(void)
{
    while(!PIR1bits.RC1IF)
    {
    }

    if(1 == RCSTAbits.OERR)
    {
        // EUSART1 error - restart

        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    return RCREG;
}

void EUSART1_Write(uint8_t txData)
{
    while(0 == PIR1bits.TX1IF)
    {
    }

    TXREG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART1_Read();
}

void putch(char txData)
{
    EUSART1_Write(txData);
}
