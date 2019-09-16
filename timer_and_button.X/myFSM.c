#include "myFSM.h"
#include "config.h"

void FSM(){
    LATD = ledValue;
    switch(state) {
            case INIT:
                if(countRA5 > 0) {
                    ledValue++;
                    printf("Increase\n");
                    state = INCREASE0;
                }
                else if(countRB0 > 0) {
                    ledValue--;
                    printf("Decrease\n");
                    state = DECREASE0;
                }
                break;
            case INCREASE0:
                if(countRA5 > TIME_PRESSED1) 
                    state = INCREASE1;
                else if (countRA5 == 0)
                    if(countRB0 > 0)
                        state = DECREASE0;
                    else 
                        state = INIT;
                break;
            case INCREASE1:
                if(increase1) {
                    ledValue++;
                    printf("Increase\n");
                    increase1 = 0;
                }
                if(countRA5 > TIME_PRESSED2)
                    state = INCREASE2;
                else if(countRA5 == 0)
                    if(countRB0 > 0)
                        state = DECREASE0;
                    else 
                        state = INIT;
                break;
            case INCREASE2:
                if(increase2) {
                    ledValue++;
                    printf("Increase\n");
                    increase2 = 0;
                }
                if(countRA5 == 0)
                    if(countRB0 > 0)
                        state = DECREASE0;
                    else 
                        state = INIT;
                break;
            case DECREASE0:
                if(countRB0 > TIME_PRESSED1)
                    state = DECREASE1;
                else if (countRB0 == 0)
                    if(countRA5 > 0)
                        state = INCREASE0;
                    else 
                        state = INIT;
                break;
            case DECREASE1:
                if(decrease1) {
                    ledValue--;
                    printf("Decrease\n");
                    decrease1 = 0;
                }
                if(countRB0 > TIME_PRESSED2)
                    state = DECREASE2;
                else if(countRB0 == 0)
                    if(countRA5 > 0)
                        state = INCREASE0;
                    else 
                        state = INIT;
                break;
            case DECREASE2:
                if(decrease2) {
                    ledValue--;
                    printf("Decrease\n");
                    decrease2 = 0;
                }
                if(countRB0 == 0)
                    if(countRA5 > 0)
                        state = INCREASE0;
                    else 
                        state = INIT;
                break;
        }
}
