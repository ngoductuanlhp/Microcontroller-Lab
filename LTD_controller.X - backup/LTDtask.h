/* 
 * File:   LTDtask.h
 * Author: Tuan
 *
 * Created on November 11, 2019, 2:38 PM
 */

#ifndef LTDTASK_H
#define	LTDTASK_H

#include "config.h"

void LTD_initialize(void);
void turn_on_heater(void);
void turn_off_heater(void);
void turn_on_heat_pump(void);
void turn_off_heat_pump(void);

void turn_on_fan(int idx);
void turn_off_fan(int idx);

void force_turn_off(void);
void set_speed_fan3(int dutyCycle);

#endif	/* LTDTASK_H */

