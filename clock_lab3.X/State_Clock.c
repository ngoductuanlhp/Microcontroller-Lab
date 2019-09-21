#include "State_Clock.h"


void handle_Time(void) {
    if (sec > 59) {
        sec = 0;                // Set seconds to 0
        min++;                  // Increment minutes
        LCDMoveCursor(1, 6);
        LCDPutChar(sec/10+'0');
        LCDPutChar(sec%10+'0');
        LCDMoveCursor(1, 3);
        LCDPutChar(min/10+'0');
        LCDPutChar(min%10+'0');
    }
    if (min > 59) {
        min = 0;                // Set minutes to 0
        hr++;                   // Increment hours
        LCDMoveCursor(1, 3);
        LCDPutChar(min/10+'0');
        LCDPutChar(min%10+'0');
        LCDMoveCursor(1, 0);
        LCDPutChar(hr/10+'0');
        LCDPutChar(hr%10+'0');
    }
    if (hr > 23 ) {
        hr = 0;                     // Set hour to 1
        LCDMoveCursor(1, 0);
        LCDPutChar(hr/10+'0');
        LCDPutChar(hr%10+'0');
    }
}

void disp_Clock (void) {
    // Display clock on LCD Line 1
    mCURSOR_LINE2;
    LCDPutChar(hr/10+'0');
    LCDPutChar(hr%10+'0');
    LCDPutChar(':');
    LCDPutChar(min/10+'0');
    LCDPutChar(min%10+'0');
    LCDPutChar(':');
    LCDPutChar(sec/10+'0');
    LCDPutChar(sec%10+'0');
    LCDPutStr("       ");

//    // Send hour, minute and second values to host PC serial terminal
//    printf("%02d:", hr);
//    printf("%02d:", min);
//    printf("%02d \t", sec);
}

void disp_Clock_Hide(unsigned char state) {
    switch(state) {
        case STATE_MOD_HOUR:
            LCDPrint(1, 0, "  ");
            break;
        case STATE_MOD_MINUTE:
            LCDPrint(1, 3, "  ");
            break;
        case STATE_MOD_SECOND:
            LCDPrint(1, 6, "  ");
            break;
        default:
            return;
    }
}

void state_clock(void) {
    // Display Clock text and Now/Next options on LCD
    mCURSOR_LINE1;
    LCDPutStr("Clock   RA5=Next");
    disp_Clock();
    while(state == STATE_CLOCK) {
        LATD = ledValue;
        if(buttonRA5) {
            buttonRA5 = 0;
            state = STATE_MOD_HOUR;
            return;
        }
        if(second_flag == 1) {
            sec++;                      // Increment seconds
            LCDMoveCursor(1, 6);
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            handle_Time();
            ledValue = (ledValue == 0) ? 255 : 0;
            second_flag = 0;
        }
    }
}