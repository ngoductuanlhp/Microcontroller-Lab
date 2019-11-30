/* 
 * File:   config.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:11 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

#define MAX_SIZE 20
#define NULL_VAL 105
#define ERROR_VAL 109
#define PERIOD 10000
#define TIME_OUT 30000

#define ERROR_SENSOR_VAL 5



#define HUMIDITY_THRESHOLD1 90
#define HUMIDITY_THRESHOLD2 80

#define _XTAL_FREQ  8000000

#define INTERRUPT_INTERVAL 10

typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)(void*);

char task_id[MAX_SIZE] = {0};

char value = 0;

char RA5_pressed = 0;
char RB0_pressed = 0;

volatile char max_temperature = 80;
volatile char min_humidity = 20;

char humidity_value;
char temperature_value;

int period = 10000;

char ledVal = 0;

enum State{IDLE, HEATER, HEAT_PUMP, TERMINATE};

volatile enum State state = IDLE;

enum State_Set_Time{IDLE_STATE, SETTING1, SETTING2, SETTING3, FINISH};

volatile enum State_Set_Time state_settime = IDLE_STATE;

char flag_change_state = 0;
tWORD check_timeout = 0;

#endif	/* CONFIG_H */

