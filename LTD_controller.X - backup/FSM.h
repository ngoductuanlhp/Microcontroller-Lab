/* 
 * File:   FSM.h
 * Author: Tuan
 *
 * Created on November 11, 2019, 2:49 PM
 */

#ifndef FSM_H
#define	FSM_H

#include "config.h"
#include "clock.h"
#include "LTDtask.h"
#include "lcd.h"

char flag_switch_state = 0;
tWORD count_timeout = 0;

void check_humid_to_turn_fan(void);
void changeState(void);
void FSM(void);


#endif	/* FSM_H */

