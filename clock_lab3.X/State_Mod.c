#include "State_Mod.h"
#include "State_Clock.h"
#include "SPI_LCD.h"


void state_mod_hour(void) {
    mCURSOR_LINE1;
    LCDPutStr("Mod H   RA5=Next");
    disp_Clock();
    while(state == STATE_MOD_HOUR) {
        LATD = ledValue;
        if(buttonRA5) {
            state = STATE_MOD_MINUTE;
            buttonRA5 = 0;
            return;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            LCDMoveCursor(1, 6);
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            LCDMoveCursor(1, 0);
            LCDPutChar(hr/10+'0');
            LCDPutChar(hr%10+'0');
            handle_Time();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            hr++;
            LCDMoveCursor(1, 0);
            LCDPutChar(hr/10+'0');
            LCDPutChar(hr%10+'0');
            handle_Time();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}

void state_mod_minute(void) {
    mCURSOR_LINE1;
    LCDPutStr("Mod M   RA5=Next");
    disp_Clock();
    while(state == STATE_MOD_MINUTE) {
        if(buttonRA5) {
            state = STATE_MOD_SECOND;
            buttonRA5 = 0;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            LCDMoveCursor(1, 6);
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            LCDMoveCursor(1, 3);
            LCDPutChar(min/10+'0');
            LCDPutChar(min%10+'0');
            handle_Time();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            min++;
            LCDMoveCursor(1, 3);
            LCDPutChar(min/10+'0');
            LCDPutChar(min%10+'0');
            handle_Time();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}

void state_mod_second(void) {
    mCURSOR_LINE1;
    LCDPutStr("Mod S   RA5=Next");
    disp_Clock();
    while(state == STATE_MOD_SECOND) {
        if(buttonRA5) {
            state = STATE_STOP_WATCH;
            buttonRA5 = 0;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            LCDMoveCursor(1, 6);
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            handle_Time();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            sec++;
            LCDMoveCursor(1, 6);
            LCDPutChar(sec/10+'0');
            LCDPutChar(sec%10+'0');
            handle_Time();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}