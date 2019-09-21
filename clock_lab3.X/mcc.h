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

#define _XTAL_FREQ  10000000

#define TIME_INTERRUPT_MS 10

#define TIME_INTERVAL_1S 1000 / TIME_INTERRUPT_MS

#define TIME_INTERVAL_100MS 100 / TIME_INTERRUPT_MS

#define TIME_INTERVAL1_MS 500 / TIME_INTERRUPT_MS
#define TIME_INTERVAL2_MS 100 / TIME_INTERRUPT_MS
#define TIME_PRESSED1_MS 1000 / TIME_INTERRUPT_MS
#define TIME_PRESSED2_MS 3000 / TIME_INTERRUPT_MS

#define HIDE_INTERVAL 800 / TIME_INTERRUPT_MS

enum State{STATE_CLOCK, STATE_MOD_HOUR, STATE_MOD_MINUTE, STATE_MOD_SECOND, STATE_STOP_WATCH};

volatile enum State state = STATE_CLOCK;

unsigned short int counter_low = 0;
unsigned short int counter_high = 0;

unsigned char buttonRA5 = 0;
unsigned char buttonRB0 = 0;

unsigned char second_flag = 0;
unsigned char hide_flag = 0;
unsigned char ms_flag = 0;

unsigned int count = 0;

unsigned char ledValue = 0;

volatile unsigned char hr = 0, min = 0, sec = 0, timeset = 0;

void SYSTEM_Initialize(void);

void state_clock(void);
void state_mod_hour(void);
void state_mod_minute(void);
void state_mod_second(void);
void state_stop_watch(void);
#endif	/* MCC_H */

