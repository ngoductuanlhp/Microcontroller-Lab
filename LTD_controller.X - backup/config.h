/* 
 * File:   config.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 9:58 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

#define MAX_SIZE 20
#define NULL_VAL 105
#define ERROR_VAL 109
#define PERIOD 10000
#define TIME_OUT 300000

#define ERROR_SENSOR_VAL 399

#define MAX_TEMPERATURE 80
#define MIN_HUMIDITY 10

#define HUMIDITY_THRESHOLD1 90
#define HUMIDITY_THRESHOLD2 80

#define _XTAL_FREQ  8000000

#define INTERRUPT_INTERVAL 10

typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)(void*);

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

char task_id[MAX_SIZE] = {0};

char value = 0;

char RA5_pressed = 0;
char RB0_pressed = 0;

float humidity_value;
float temperature_value;

int period = 10000;

enum State{IDLE, HEATER, HEAT_PUMP, SET_TIMER};

volatile enum State state = IDLE;

char ledVal = 0;

#endif	/* CONFIG_H */

