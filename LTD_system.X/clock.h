/* 
 * File:   clock.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:19 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "config.h"

typedef struct {
    tWORD delay_t;
    tWORD period_t;
    FUNCTION_PTR func_ptr;
    int next;
    void* data_p;
} task_struct;

typedef struct {
    FUNCTION_PTR func_ptr;
    void* data_p;
} queue_node;

#define TMR0_PRELOAD 100
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

