/* 
 * File:   config.h
 * Author: Tuan
 *
 * Created on September 16, 2019, 8:47 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "timer_manager.h"
#include "buttons.h"
#include "myFSM.h"
#include "osc_manager.h"
    
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
    
#define TIME_INTERRUPT_MS 10
#define TIME_INTERVAL1_MS 500 / TIME_INTERRUPT_MS
#define TIME_INTERVAL2_MS 100 / TIME_INTERRUPT_MS
#define TIME_PRESSED1_MS 1000 / TIME_INTERRUPT_MS
#define TIME_PRESSED2_MS 5000 / TIME_INTERRUPT_MS
    
typedef unsigned char tBYTE;
typedef unsigned int tWORD;
    
enum State{INIT, INCREASE0, INCREASE1, INCREASE2, DECREASE0, DECREASE1, DECREASE2};
volatile enum State state = INIT;

tBYTE ledValue = 0;

tBYTE buttonRA5 = 0;

tBYTE buttonRB0 = 0;

tWORD countRA5 = 0;
tBYTE increase1 = 0;
tBYTE increase2 = 0;

tWORD countRB0 = 0;
tBYTE decrease1 = 0;
tBYTE decrease2 = 0;

tBYTE counter_low = 0;
tBYTE counter_high = 0;

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

