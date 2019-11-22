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


int remove_task_counter = 0;


//void blinking_LED(void *idx_ptr) {
//    char idx = (char)idx_ptr;
//    LED_state[idx] = !LED_state[idx];
//    switch(idx) {
//        case 0: LATDbits.LATD0 = LED_state[idx];
//            break;
//        case 1: LATDbits.LATD1 = LED_state[idx];
//            break;
//        case 2: LATDbits.LATD2 = LED_state[idx];
//            break;
//        case 3: LATDbits.LATD3 = LED_state[idx];
//            break;
//        case 4: LATDbits.LATD4 = LED_state[idx];
//            break;
//        case 5: LATDbits.LATD5 = LED_state[idx];
//            break;
//        case 6: LATDbits.LATD6 = LED_state[idx];
//            break;
//        case 7: LATDbits.LATD7 = LED_state[idx];
//            break;
//    }
//}

void printTime_ms(void* data_ptr) {
    tWORD current_time = get_time();
    char i = 2;
    while(current_time > 0 && i < 10) {
        char temp = current_time % 10 + '0';
        LCDPrintChar(0, 15 - i, temp);
        current_time/= 10;
        i++;
    }
}

void printTempAndHumid(void) {
    LCDPrint(1, 0, "T:");
    LCDPrint(1, 8, "H:");
    int temp = (temperature_value == ERROR_SENSOR_VAL) ? 0 : 110 * temperature_value;
    int humid = (humidity_value == ERROR_SENSOR_VAL) ? 0 : 10 * humidity_value;
    LCDPrintChar(1, 2, temp / 100);
    temp /= 10;
    LCDPrintChar(1, 3, temp / 10);
    LCDPrintChar(1, 4, temp % 10);
    
    LCDPrintChar(1, 2, humid / 100);
    humid /= 10;
    LCDPrintChar(1, 3, humid / 10);
    LCDPrintChar(1, 4, humid % 10);
}

void main(void) {
    system_initialize();
    
//    task_id[0] = register_timer(500, 0, blinking_LED, 0);
//    task_id[1] = register_timer(1000, 200, blinking_LED, 1);
//    task_id[2] = register_timer(3000, 4000, blinking_LED, 2);
//    task_id[3] = register_timer(9000, 60, blinking_LED, 3);
//    task_id[4] = register_timer(5500, 100, blinking_LED, 4);
//    task_id[5] = register_timer(3000, 8000, blinking_LED, 5);
//    task_id[6] = register_timer(100, 400, blinking_LED, 6);
//    task_id[7] = register_timer(100, 400, blinking_LED, 7);
    
    task_id[0] = register_timer(50, 0, printTime_ms, ((void*)0));
    task_id[1] = register_timer(20, 70, handleButton, ((void*)0));
    task_id[2]  = register_timer(2000, 35, readTempAndHumid, ((void*)0));
    task_id[3] = register_timer(2000, 23, printTempAndHumid, ((void*)0));
    
    //LCDPrint(0, 0, "Lab 4    1710364");
    LCDPrint(0, 0, "Time");
    LCDPrint(0, 14, "ms");
    while(1) {
        dispatch();
//        if(RA5_pressed == 1) {
//            RA5_pressed = 0;
//            printTime_ms(NULL);
//        }
//        if(RB0_pressed == 1) {
//            RB0_pressed = 0;
//            remove_timer(remove_task_counter);
//            remove_task_counter = (remove_task_counter + 1) % MAX_SIZE;
//        }
    }
    return;
}
