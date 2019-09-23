#include "State_Clock.h"

void disp_Changed(void) {
    if(sec_changed_flag) {
        sec_changed_flag = 0;
        LCDMoveCursor(1, 6);
        LCDPutChar(sec/10+'0');
        LCDPutChar(sec%10+'0');
    }
    if(min_changed_flag) {
        min_changed_flag = 0;
        LCDMoveCursor(1, 3);
        LCDPutChar(min/10+'0');
        LCDPutChar(min%10+'0');
    }
    if(hr_changed_flag) {
        hr_changed_flag = 0;
        LCDMoveCursor(1, 0);
        LCDPutChar(hr/10+'0');
        LCDPutChar(hr%10+'0');
    }
}

void handle_Time(void) {
    sec_changed_flag = 1;
    if (sec > 59) {
        sec = 0;
        min++;
        min_changed_flag = 1;
    }
    if (min > 59) {
        min = 0;
        hr++;
        hr_changed_flag = 1;
    }
    if (hr > 23 ) {
        hr = 0;
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
}

void disp_Clock_Hide(unsigned char state) {
    switch(state) {
        case STATE_SET_HOUR:
            LCDPrint(1, 0, "  ");
            break;
        case STATE_SET_MINUTE:
            LCDPrint(1, 3, "  ");
            break;
        case STATE_SET_SECOND:
            LCDPrint(1, 6, "  ");
            break;
        default:
            return;
    }
}

void state_clock(void) {
    if(changed_state_flag) {
        changed_state_flag = 0;
        mCURSOR_LINE1;
        LCDPutStr("Clock     RA5=->");
        disp_Clock();
    }
    if(second_flag == 1) {
        second_flag = 0;
        sec++;
        handle_Time();
        disp_Changed();
        ledValue = (ledValue == 0) ? 255 : 0;        
    }
}