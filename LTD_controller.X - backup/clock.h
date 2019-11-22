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
#define TMR1H_PRELOAD 0xB1
#define TMR1L_PRELOAD 0xE0

tWORD time_ms;
tWORD prev_time_ms = 0;

int start_timer(char timer_vaddr);
tWORD get_time(void);
char register_timer(tWORD period, tWORD delay, FUNCTION_PTR callback, void* data_ptr);
int remove_timer(char id);
int stop_timer(void);
int timer_ISR();
void dispatch(void);

#endif	/* CLOCK_H */

