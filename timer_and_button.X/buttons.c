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
        countRA5++;
        if(countRA5 % TIME_INTERVAL2 == 0)
            increase2 = 1;
        if(countRA5 % TIME_INTERVAL1 == 0)
            increase1 = 1;
    }
    else if(checkRB0 == 2) {
        countRA5 = 0;
        countRB0++;
        if(countRB0 % TIME_INTERVAL2 == 0)
            decrease2 = 1;
        if(countRB0 % TIME_INTERVAL1 == 0)
            decrease1 = 1;
    }
    else if(checkRB0 == 1 || checkRA5 == 1) {
        countRA5 = 0;
        countRB0 = 0;
    }
}
