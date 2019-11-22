/* 
 * File:   mcc.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:17 AM
 */

#ifndef MCC_H
#define	MCC_H

#include "config.h"
#include "lcd.h"
#include "clock.h"
#include "buttons.h"
#include "dht11.h"
#include "LTDtasks.h"

void system_initialize(void);
void changeState(void);
void check_humid_to_turn_fan(void);
void print_temp_and_humid(void);

#endif	/* MCC_H */

