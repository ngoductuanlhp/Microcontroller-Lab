#include "state_clock.h"

void display_clock() {
   mCURSOR_LINE1; 
   LCDPutChar(hour/10+'0');
   LCDPutChar(hour%10+'0');
   LCDPutChar(':');
   LCDPutChar(min/10+'0');
   LCDPutChar(min%10+'0');
   LCDPutChar(':');
   LCDPutChar(sec/10+'0');
   LCDPutChar(sec%10+'0');
   LCDPutStr("        ");
   // Send hour, minute and second values to host PC serial terminal
   printf("%02d:", hour);
   printf("%02d:", min);
   printf("%02d \t", sec);
}

void clock(void) {
    mCURSOR_LINE2;
    LCDPutStr("RA5=MODIFY_HOUR");  // Display Menu/Set on LCD Line 2
    printf("RA5=MODIFY_HOUR\n\r"); // Send Menu/Set to host PC serial terminal
    while(state == CLOCK) {
        if(timerflag_1s == 1) {
            sec++;
            if(sec > 59) {
                sec = 0;
                min++;
            }
            if(min > 59) {
                min = 0;
                hour++;
            }
            if(hour > 23) {
                hour = 0;
            }
            display_clock();
            timerflag_1s = 0;   
        }
        if(checkRA5 == 1) {
            checkRA5 = 0;
            state = MODIFY;
        }           
    }
}
