/* 
 * File:   clock.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 10:17 PM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include <xc.h>
#include "task.h"
#include "config.h"

#define TMR0_PRELOAD 131

unsigned long int time_ms;

int start_timer(char timer_vaddr);
unsigned long int get_time(void);
char register_timer(unsigned long int period, unsigned long int delay, FUNCTION_PTR callback, void* data);
int remove_timer(char id);
int stop_timer(void);
int timer_ISR();
void dispatch(void);

#endif	/* CLOCK_H */

