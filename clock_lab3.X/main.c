/*
 * File:   main.c
 * Author: Tuan
 *
 * Created on September 20, 2019, 1:53 PM
 */
#include "mcc.h"

void main(void) {
    SYSTEM_Initialize();
    while(1) {
        LATD = ledValue;
        if(buttonRA5) {
            buttonRA5 = 0;
            state = (state + 1) % 5;
            changed_state_flag = 1;
        }
        switch(state) {
            case STATE_CLOCK: state_clock();
                break;
            case STATE_SET_HOUR: state_set_hour();
                break;
            case STATE_SET_MINUTE: state_set_minute();
                break;
            case STATE_SET_SECOND: state_set_second();
                break;
            case STATE_STOP_WATCH: state_stop_watch();
                break;
            default: state_clock();
                break;
        }
    }
    return;
}
