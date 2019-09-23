/* 
 * File:   mcc.h
 * Author: Tuan
 *
 * Created on September 20, 2019, 1:56 PM
 */
#ifndef MCC_H
#define	MCC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "osc_manager.h"
#include "pin_manager.h"
#include "timer0_manager.h"
#include "SPI_LCD.h"
#include "buttons.h"

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

#define _XTAL_FREQ  8000000

#define TIME_INTERRUPT_MS 10

#define TIME_INTERVAL_1S 1000 / TIME_INTERRUPT_MS

#define TIME_INTERVAL_10MS 10 / TIME_INTERRUPT_MS

#define TIME_INTERVAL1_MS 500 / TIME_INTERRUPT_MS
#define TIME_INTERVAL2_MS 100 / TIME_INTERRUPT_MS
#define TIME_PRESSED1_MS 1000 / TIME_INTERRUPT_MS
#define TIME_PRESSED2_MS 3000 / TIME_INTERRUPT_MS

#define HIDE_INTERVAL 700 / TIME_INTERRUPT_MS

typedef unsigned char tBYTE;
typedef unsigned short int tHALFWORD;
typedef unsigned int tWORD;

enum State{STATE_CLOCK, STATE_SET_HOUR, STATE_SET_MINUTE, STATE_SET_SECOND, STATE_STOP_WATCH};

volatile enum State state = STATE_CLOCK;

tBYTE counter_low = 0;
tBYTE counter_high = 0;

tBYTE buttonRA5 = 0;
tBYTE buttonRB0 = 0;

tBYTE second_flag = 0;
tBYTE hide_flag = 0;
tBYTE ms_flag = 0;

tBYTE sec_changed_flag = 0;
tBYTE min_changed_flag = 0;
tBYTE hr_changed_flag = 0;

tBYTE changed_state_flag = 1;

tWORD count = 0;

tBYTE ledValue = 0;

volatile tBYTE hr = 0, min = 0, sec = 0;

void SYSTEM_Initialize(void);

void state_clock(void);
void state_set_hour(void);
void state_set_minute(void);
void state_set_second(void);
void state_stop_watch(void);
#endif	/* MCC_H */

