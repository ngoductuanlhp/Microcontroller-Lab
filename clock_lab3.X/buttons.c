#include "buttons.h"
#include "mcc.h"

#define PRESSED 0
#define RELEASE 1

unsigned char firstReadRA5 = RELEASE;
unsigned char secondReadRA5 = RELEASE;
unsigned char firstReadRB0 = RELEASE;
unsigned char secondReadRB0 = RELEASE;

unsigned char stateRA5 = 0;
unsigned int countRA5 = 0;
unsigned int countRA5_1 = 0;

unsigned char stateRB0 = 0;
unsigned int countRB0 = 0;
unsigned int countRB0_1 = 0;


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
    if(checkRA5 == 2) {
        stateRB0 = 0;
        countRB0 = 0;
        countRB0_1 = 0;
        switch(stateRA5) {
            case 0:
                buttonRA5 = 1;
                stateRA5 = 1;
                break;
            case 1:
                countRA5++;
                if(countRA5 >= TIME_PRESSED1_MS) {
                    buttonRA5 = 1;
                    stateRA5 = 2;
                }
                break;
            case 2:
                countRA5++;
                countRA5_1++;
                if(countRA5_1 == TIME_INTERVAL1_MS) {
                    buttonRA5 = 1;
                    countRA5_1 = 0;
                }
                if(countRA5 >= TIME_PRESSED2_MS) {
                    buttonRA5 = 1;
                    stateRA5 = 3;
                }
                break;
            case 3:
                countRA5++;
                if(countRA5 >= TIME_INTERVAL2_MS) {
                    buttonRA5 = 1;
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
                buttonRB0 = 1;
                stateRB0 = 1;
                break;
            case 1:
                countRB0++;
                if(countRB0 >= TIME_PRESSED1_MS) {
                    buttonRB0 = 1;
                    stateRB0 = 2;
                }
                break;
            case 2:
                countRB0++;
                countRB0_1++;
                if(countRB0_1 == TIME_INTERVAL1_MS) {
                    buttonRB0 = 1;
                    countRB0_1 = 0;
                }
                if(countRB0 >= TIME_PRESSED2_MS) {
                    buttonRB0 = 1;
                    stateRB0 = 3;
                }
                break;
            case 3:
                countRB0++;
                if(countRB0 >= TIME_INTERVAL2_MS) {
                    buttonRB0 = 1;
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

