#include "buttons.h"

#define PRESSED 0
#define RELEASE 1

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

void handleButton() {
    int checkRA5 = readButtonRA5();
    int checkRB0 = readButtonRB0();
    switch(stateRA5) {
        case 0:
            if(checkRA5 == 2) {
                stateRA5 = 1;
                RA5_pressed = 1;
            }
            break;
        case 1:
            if(checkRA5 == 1)
                stateRA5 = 0;
            break;
    }
    switch(stateRB0) {
        case 0:
            if(checkRB0 == 2) {
                stateRB0 = 1;
                RB0_pressed = 1;
            }
            break;
        case 1:
            if(checkRB0 == 1)
                stateRB0 = 0;
            break;
    }
}
