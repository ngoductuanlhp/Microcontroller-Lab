/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on November 22, 2019, 1:27 PM
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

#include "lcd.h"
#include "dht.h"
#include <xc.h>



void print_temp_and_humid(void) {
    LCDPrint(1, 0, "T:");
    LCDPrint(1, 6, "H:");
    if(temperature_value == ERROR_SENSOR_VAL) {
        LCDPrint(1, 3, "ER");
    } else{
        LCDPrintChar(1, 3, temperature_value / 10 + '0');
        LCDPrintChar(1, 4, temperature_value % 10 + '0');
    }
    if(humidity_value == ERROR_SENSOR_VAL) {
        LCDPrint(1, 8, "ER");
    } else {
        LCDPrintChar(1, 8, humidity_value / 10 + '0');
        LCDPrintChar(1, 9, humidity_value % 10 + '0');
    }
}

void main(void) {
    OSCCON = 0x70;
    mOPEN_LCD;
    LCDPrint(0, 0, "hello world");
    __delay_ms(2000);
    TRISD = 0x00;
    ledVal = 0xFF;
    
    while(1) {
        LATD = ledVal;
        readTempAndHumid();
        print_temp_and_humid();
        __delay_ms(10000); 
    }
    return;
}
