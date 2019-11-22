/* 
 * File:   LTDtasks.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:28 AM
 */

#ifndef LTDTASKS_H
#define	LTDTASKS_H

#include "config.h"

void turn_on_heater(void);
void turn_off_heater(void);
void turn_on_heat_pump(void);
void turn_off_heat_pump(void);

void turn_on_fan(int idx);
void turn_off_fan(int idx);

void force_turn_off(void);
void set_speed_fan3(int dutyCycle);

#endif	/* LTDTASKS_H */

