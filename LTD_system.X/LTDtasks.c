#include "LTDtasks.h"

void turn_on_heater(void) {
    LATDbits.LATD0 = 1;
}

void turn_off_heater(void) {
    LATDbits.LATD0 = 0;
}

void turn_on_heat_pump(void) {
    LATDbits.LATD1 = 1;
}

void turn_off_heat_pump(void) {
    LATDbits.LATD1 = 0;
}

void turn_on_fan(int idx) {
    switch (idx) {
        case 1:
            LATDbits.LATD7 = 1;
            break;
        case 2:
            LATDbits.LATD6 = 1;
            break;
    }
}

void turn_off_fan(int idx) {
    switch (idx) {
        case 1:
            LATDbits.LATD7 = 0;
            break;
        case 2:
            LATDbits.LATD6 = 0;
            break;
        case 3:
            LATDbits.LATD5 = 0;
            break;
    }
}

void set_speed_fan3(int dutyCycle) {
    CCPR4L = 24 * dutyCycle;
    if(dutyCycle > 0)
        LATDbits.LATD5 = 1;
    else LATDbits.LATD5 = 0;
}

void force_turn_off(void) {
    turn_off_fan(1);
    turn_off_fan(2);
    set_speed_fan3(0);
    turn_off_heat_pump();
    turn_off_heater();
}
