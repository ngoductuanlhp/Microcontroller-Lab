/* 
 * File:   config.h
 * Author: Tuan
 *
 * Created on September 14, 2019, 1:33 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "BBSPI_LCD.h"

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
    
#define pressed 0
    
    //#define _XTAL_FREQ  1000000
#define _XTAL_FREQ  10000000
    
enum State{CLOCK, MODIFY, STOP_WATCH};
volatile enum State state;

volatile unsigned char hour = 0, min = 0, sec = 0;

unsigned char timerflag_10ms = 0;
unsigned char timerflag_1s = 0;

unsigned int count = 0;

unsigned char firstReadRA5 = 1;
unsigned char secondReadRA5 = 1;

unsigned char buttonRA5 = 0;
unsigned char buttonRA5_1s_pressed = 0;
unsigned int countRA5 = 0;
unsigned int countRA5_1 = 0;
unsigned int checkRA5 = 0;

void clock(void);

void modify(void);

void stop_watch(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

