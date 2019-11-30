/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:10 AM
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

#include <xc.h>
#include "config.h"
#include "mcc.h"


char isSet = 0;


void set_time_process(void) {
    switch(state_settime) {
        case IDLE_STATE: 
            if(RB0_pressed) {
                RB0_pressed = 0;
                isSet = 1;
                state_settime = 1;
                mLCD_CLEAR;
                LCDPrint(0, 0, "Set time");
                int temp = period/1000;
                LCDPrintChar(0, 10, temp / 10 + '0');
                LCDPrintChar(0, 11, temp % 10 + '0');
                LCDPrintChar(0, 12, 's');
                __delay_ms(2000);
            }
            break;
        case SETTING1:
            if(RA5_pressed) {
                RA5_pressed = 0;

                period+= 1000;
                if(period >= 20000)
                    period = 1000;
                int temp = period/1000;
                LCDPrintChar(0, 10, temp / 10 + '0');
                LCDPrintChar(0, 11, temp % 10 + '0');
                LCDPrintChar(0, 12, 's');
            }
            if(RB0_pressed) {
                RB0_pressed = 0;
                remove_timer(task_id[1]);
                task_id[1] = register_timer(period, 0, changeState, ((void*)0));
                state_settime = 2;
                mLCD_CLEAR;
                LCDPrint(0, 0, "Set temp");
                LCDPrintChar(0, 10, max_temperature / 10 + '0');
                LCDPrintChar(0, 11, max_temperature % 10 + '0');
            }
            break;
        case SETTING2:
            if(RA5_pressed) {
                RA5_pressed = 0;

                max_temperature+= 1;
                if(max_temperature >= 100)
                    max_temperature = 27;
//                int temp = max_temperature;
                LCDPrintChar(0, 10, max_temperature / 10 + '0');
                LCDPrintChar(0, 11, max_temperature % 10 + '0');
//                LCDPrintChar(0, 12, 's');
            }
            if(RB0_pressed) {
                RB0_pressed = 0;
                state_settime = 3;
                mLCD_CLEAR;
                LCDPrint(0, 0, "Set humid");
                LCDPrintChar(0, 10, min_humidity / 10 + '0');
                LCDPrintChar(0, 11, min_humidity % 10 + '0');
            }
            break;
        case SETTING3:
            if(RA5_pressed) {
                RA5_pressed = 0;

                min_humidity-= 1;
                if(min_humidity <= 10)
                    min_humidity = 80;
//                int temp = MIN_HUMIDITY;
                LCDPrintChar(0, 10, min_humidity / 10 + '0');
                LCDPrintChar(0, 11, min_humidity % 10 + '0');
//                LCDPrintChar(0, 12, 's');
            }
            if(RB0_pressed) {
                RB0_pressed = 0;
                state_settime = 4;
            }
            break;
        case FINISH:
            isSet = 0;
            state_settime = 0;
            LCDPrint(0, 0, "Set successful");
            __delay_ms(2000);
            LCDPrint(0, 0, "              ");
            if(state == HEATER) LCDPrint(0, 0, "Heater");
            else if(state == HEAT_PUMP) LCDPrint(0, 0, "Heat Pump");
            break;
    }
}

void LTD_process(void) {
    switch(state) {
        case IDLE:
            if(RA5_pressed) {
                RA5_pressed = 0;
                state = HEATER;
                check_timeout = get_time();
                turn_on_heater();
                turn_on_fan(1);
                LCDPrint(0, 0, "              ");
                LCDPrint(0, 0, "Heater");
            }
            break;
        case HEATER:
            if(get_time() - check_timeout > TIME_OUT) {
                mLCD_CLEAR;
                LCDPrint(0, 0, "ERROR - TURN OFF");
                state = TERMINATE;
            }
            if(flag_change_state) {
                flag_change_state = 0;
                if(!isSet) {
                    LCDPrint(0, 0, "              ");
                    LCDPrint(0, 0, "Heat Pump");
                }

                state = HEAT_PUMP;
                check_timeout = get_time();

                turn_off_heater();
                turn_off_fan(1);
                turn_on_heat_pump();
                turn_on_fan(2);
            }
            break;
        case HEAT_PUMP:
            if(get_time() - check_timeout > TIME_OUT) {
                mLCD_CLEAR;
                LCDPrint(0, 0, "ERROR - TURN OFF");
                state = TERMINATE;
            }
            if(flag_change_state) {
                flag_change_state = 0;

                if(!isSet) {
                    LCDPrint(0, 0, "              ");
                    LCDPrint(0, 0, "Heater");
                }

                state = HEATER;
                check_timeout = get_time();

                turn_off_heat_pump();
                turn_off_fan(2);
                turn_on_heater();
                turn_on_fan(1);
            }
            break;
        case TERMINATE:
            LCDPrint(0, 0, "              ");
            LCDPrint(0, 0, "Finish");
            LCDPrint(1, 0, "T:");
            LCDPrint(1, 6, "H:");
            int temp = (int)temperature_value;
            int humid = (int)humidity_value;
            LCDPrintChar(1, 3, temp / 10 + '0');
            LCDPrintChar(1, 4, temp % 10 + '0');
            LCDPrintChar(1, 8, humid / 10 + '0');
            LCDPrintChar(1, 9, humid % 10 + '0');
            __delay_ms(2000);
            turn_off_heater();
            turn_off_fan(1);
            turn_off_heat_pump();
            turn_off_fan(2);
            check_timeout = 0;
            state = IDLE;
            RA5_pressed = 0;
            LCDPrint(0, 0, "              ");
            LCDPrint(0, 0, "IDLE");
            break;
    }
}

void main(void) {
    system_initialize();
    
    task_id[0] = register_timer(50, 0, handleButton, ((void*)0));
    task_id[1] = register_timer(period, 5000, changeState, ((void*)0));
    task_id[2] = register_timer(4000, 3100, check_humid_to_turn_fan, ((void*)0));
    task_id[3] = register_timer(4000, 3300, readTempAndHumid, ((void*)0));
    task_id[4] = register_timer(4000, 1500, print_temp_and_humid, ((void*)0));
    
    LCDPrint(0, 0, "LTD controller  ");
    LCDPrint(1, 0, "ID: 1710364     ");
    
    __delay_ms(2000);
    mLCD_CLEAR;
    LCDPrint(0, 0, "IDLE");
    while(1) {
        set_time_process();
        LTD_process();
        dispatch();
    }
    return;
}
