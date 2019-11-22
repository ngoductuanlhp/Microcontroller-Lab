/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on November 4, 2019, 9:24 AM
 */
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

#include "config.h"
#include "mcc.h"
#include <xc.h>

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

//char receive_UART() {
//   if(RCSTAbits.OERR) {
//    RCSTAbits.CREN = 0;
//    RCSTAbits.CREN = 1;
//   } 
//   while(!PIR1bits.RCIF) {
//   
//   }
//   return RCREG1;
//}

void printTempAndHumid(void) {
    LCDPrint(1, 0, "T:");
    LCDPrint(1, 8, "H:");
    int temp = (temperature_value == ERROR_SENSOR_VAL) ? 0 : 10 * temperature_value;
    int humid = (humidity_value == ERROR_SENSOR_VAL) ? 0 : 10 * humidity_value;
    LCDPrintChar(1, 2, temp / 100 + '0');
    temp /= 10;
    LCDPrintChar(1, 3, ",");
    LCDPrintChar(1, 4, temp / 10 + '0');
    LCDPrintChar(1, 5, temp % 10 + '0');
    
    LCDPrintChar(1, 2, humid / 100 + '0');
    humid /= 10;
    LCDPrintChar(1, 3, ".");
    LCDPrintChar(1, 4, humid / 10 + '0');
    LCDPrintChar(1, 5, humid % 10 + '0');
}

void system_setup(void) {
    task_id[0] = register_timer(100, 1000, handleButton, 0);//read button every 50ms
    task_id[1] = register_timer(5000, 1000, readTempAndHumid, 0);//check temperature and humidity every 5s
    task_id[2] = register_timer(5000, 0, check_humid_to_turn_fan, 0);//Change state periodically
    task_id[3] = register_timer(period, period, changeState, 0);
    task_id[4] = register_timer(10000, 3000, printTempAndHumid, 0);
}

void main(void) {
    
    system_initialize();
    
    system_setup();
//    TRISD = 0x00;
//    LATD = 0xFF;
    LCDPrint(0, 0, "LTD controller  ");
    LCDPrint(1, 0, "ID: 1710364     ");
//    TRISD = 0x00;
//    LATD = 0xF0;
    while(1) {
        dispatch();
        FSM();
    }
    return;
}
