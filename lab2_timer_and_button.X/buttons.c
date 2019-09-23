#include "buttons.h"
#include "config.h"

int readButtonRA5() {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if(secondReadRA5 == firstReadRA5) {
        return (secondReadRA5 == 0) ? 2 : 1;
    }
    return 0;
}

int readButtonRB0() {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if(secondReadRB0 == firstReadRB0) {
        return (secondReadRB0 == 0) ? 2 : 1;
    }
    return 0;
}

void handleButton() {
    int checkRA5 = readButtonRA5();
    int checkRB0 = readButtonRB0();
    if(checkRA5 == 2) {
        countRB0 = 0;
        countRB0_1 = 0;
        countRB0_2 = 0;
        countRA5++;
        countRA5_1++;
        countRA5_2++;
        if(countRA5_2 == TIME_INTERVAL2_MS) {
            countRA5_2 = 0;
            increase2 = 1;
        }
        if(countRA5_1 == TIME_INTERVAL1_MS) {
            countRA5_1 = 0;
            increase1 = 1;
        }
    }
    else if(checkRB0 == 2) {
        countRA5 = 0;
        countRA5_1 = 0;
        countRA5_2 = 0;
        countRB0++;
        countRB0_1++;
        countRB0_2++;
        if(countRB0_2 == TIME_INTERVAL2_MS) {
            countRB0_2 = 0;
            decrease2 = 1;
        }
        if(countRB0_1 == TIME_INTERVAL1_MS) {
            countRB0_1 = 0;
            decrease1 = 1;
        }
    }
    else if(checkRB0 == 1 || checkRA5 == 1) {
        countRA5 = 0;
        countRA5_1 = 0;
        countRA5_2 = 0;
        countRB0 = 0;
        countRB0_1 = 0;
        countRB0_2 = 0;
    }
}
