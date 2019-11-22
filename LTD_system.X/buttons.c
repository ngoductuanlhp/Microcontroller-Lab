#include "buttons.h"

tBYTE firstReadRA5 = RELEASE;
tBYTE secondReadRA5 = RELEASE;
tBYTE firstReadRB0 = RELEASE;
tBYTE secondReadRB0 = RELEASE;

tBYTE stateRA5 = 0;
tWORD countRA5 = 0;
tWORD countRA5_1 = 0;

tBYTE stateRB0 = 0;
tWORD countRB0 = 0;
tWORD countRB0_1 = 0;


int readButtonRA5() {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if(secondReadRA5 == firstReadRA5) {
        return (secondReadRA5 == PRESSED) ? 2 : 1;
    }
    return 0;
}

int readButtonRB0() {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if(secondReadRB0 == firstReadRB0) {
        return (secondReadRB0 == PRESSED) ? 2 : 1;
    }
    return 0;
}

void handleButton(void* data_ptr) {
    int checkRA5 = readButtonRA5();
    int checkRB0 = readButtonRB0();
    if(checkRA5 == 2) {
        stateRB0 = 0;
        countRB0 = 0;
        countRB0_1 = 0;
        switch(stateRA5) {
            case 0:
                RA5_pressed = 1;
                stateRA5 = 1;
                break;
            case 1:
                countRA5++;
                if(countRA5 >= TIME_PRESSED1_MS) {
                    RA5_pressed = 1;
                    stateRA5 = 2;
                }
                break;
            case 2:
                countRA5++;
                countRA5_1++;
                if(countRA5_1 == TIME_INTERVAL1_MS) {
                    RA5_pressed = 1;
                    countRA5_1 = 0;
                }
                if(countRA5 >= TIME_PRESSED2_MS) {
                    RA5_pressed = 1;
                    stateRA5 = 3;
                }
                break;
            case 3:
                countRA5++;
                if(countRA5 >= TIME_INTERVAL2_MS) {
                    RA5_pressed = 1;
                    countRA5 = 0;
                }
                break;
        }
    }
    else if(checkRB0 == 2) {
        stateRA5 = 0;
        countRA5 = 0;
        countRA5_1 = 0;
        switch(stateRB0) {
            case 0:
                RB0_pressed = 1;
                stateRB0 = 1;
                break;
            case 1:
                countRB0++;
                if(countRB0 >= TIME_PRESSED1_MS) {
                    RB0_pressed = 1;
                    stateRB0 = 2;
                }
                break;
            case 2:
                countRB0++;
                countRB0_1++;
                if(countRB0_1 == TIME_INTERVAL1_MS) {
                    RB0_pressed = 1;
                    countRB0_1 = 0;
                }
                if(countRB0 >= TIME_PRESSED2_MS) {
                    RB0_pressed = 1;
                    stateRB0 = 3;
                }
                break;
            case 3:
                countRB0++;
                if(countRB0 >= TIME_INTERVAL2_MS) {
                    RB0_pressed = 1;
                    countRB0 = 0;
                }
                break;
        }
    }
    else if(checkRB0 == 1 || checkRA5 == 1) {
        countRA5 = 0;
        countRA5_1 = 0;
        countRB0 = 0;
        countRB0_1 = 0;
        stateRA5 = 0;
        stateRB0 = 0;
    }
}
