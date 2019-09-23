/* 
 * File:   State_Stop_Watch.h
 * Author: Tuan
 *
 * Created on September 20, 2019, 2:48 PM
 */

#ifndef STATE_STOP_WATCH_H
#define	STATE_STOP_WATCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc.h"
#include "State_Clock.h"
    
volatile unsigned char min_sw = 0, sec_sw = 0, ms_sw = 0;
unsigned char state_sw = 0;

unsigned char ms_sw_changed_flag = 0;
unsigned char sec_sw_changed_flag = 0;
unsigned char min_sw_changed_flag = 0;

void disp_Clock_SW();
void handle_Time_SW(void);
void disp_Changed_SW(void);

#ifdef	__cplusplus
}
#endif

#endif	/* STATE_STOP_WATCH_H */

