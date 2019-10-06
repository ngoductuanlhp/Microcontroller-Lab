#include "clock.h"

int count = 0;

int start_timer(char timer_vaddr) {
    if(timer_vaddr > 4) 
        return 0;
    switch(timer_vaddr) {
        case 0:
            INTCONbits.TMR0IE = 1;
            INTCONbits.TMR0IF = 0;
            T0CON = 0xC3;
            TMR0L = TMR0_PRELOAD;// 1ms interrupt
            time_ms = 0;
            break;
        case 1:
            initializeTaskList();
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            T1CON = 0b10000001;
            TMR1H = 0xB1;
            TMR1L = 0xE0;
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
    return 1;   
}

unsigned long int get_time(void) {
    return time_ms;
}

char register_timer(unsigned long int period, unsigned long int delay, FUNCTION_PTR callback, void *data) {
    return addTask(period, delay, callback, data);
}

int remove_timer(char id) {
    return removeTask(id);
}

int stop_timer(void) {
    INTCONbits.TMR0IE = 0;
    INTCONbits.TMR0IF = 0;
    time_ms = 0;
    return 0;
}

void __interrupt() timer_interrupt(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = TMR0_PRELOAD;
        time_ms++;
    }
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xB1;
        TMR1L = 0xE0;
        handleListHead();
        count++;
        if(count == 100) {
            count = 0;
            //value++;
        }
    }
}

void dispatch(void) {
    selectReadyTask();
}

