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
    
enum State{INIT, INCREASE0, INCREASE1, INCREASE2, DECREASE0, DECREASE1, DECREASE2};
volatile enum State state = INIT;

unsigned char firstReadRA5 = 1;
unsigned char secondReadRA5 = 1;
unsigned char firstReadRB0 = 1;
unsigned char secondReadRB0 = 1;

unsigned char ledValue = 0;

unsigned char buttonRA5 = 0;

unsigned char buttonRB0 = 0;

unsigned int countRA5 = 0;
unsigned char increase1 = 0;
unsigned char increase2 = 0;

unsigned int countRB0 = 0;
unsigned char decrease1 = 0;
unsigned char decrease2 = 0;


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

