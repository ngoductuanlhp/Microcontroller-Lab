/* 
 * File:   config.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 9:58 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#define MAX_SIZE 20
#define NULL_VAL 105
#define ERROR_VAL 109

#define _XTAL_FREQ  8000000

#define INTERRUPT_INTERVAL 10

typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)();

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

char value = 0;

char RA5_pressed = 0;
char RB0_pressed = 0;

#endif	/* CONFIG_H */

