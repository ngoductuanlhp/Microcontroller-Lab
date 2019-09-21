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
        switch(state) {
            case STATE_CLOCK: state_clock();
                break;
            case STATE_MOD_HOUR: state_mod_hour();
                break;
            case STATE_MOD_MINUTE: state_mod_minute();
                break;
            case STATE_MOD_SECOND: state_mod_second();
                break;
            case STATE_STOP_WATCH: state_stop_watch();
                break;
            default: state_clock();
                break;
        }
    }
    return;
}
