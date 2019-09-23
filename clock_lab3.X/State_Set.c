#include "State_Set.h"
#include "State_Clock.h"
#include "SPI_LCD.h"


//void state_set_time(unsigned char state) {
//    mCURSOR_LINE1;
//    LCDPutStr("Set ");
//    switch(state) {
//        case STATE_SET_HOUR:
//            LCDPutStr(SET_HR);
//            break;
//        case STATE_SET_MINUTE:
//            LCDPutStr(SET_MIN);
//            break;
//        case STATE_SET_SECOND:
//            LCDPutStr(SET_SEC);
//            break;
//    }
//    LCDPutStr("   RA5=->")
//    disp_Clock();
//    while(state == STATE_SET_HOUR) {
//        LATD = ledValue;
//        if(buttonRA5) {
//            state = STATE_SET_MINUTE;
//            buttonRA5 = 0;
//            return;
//        }
//        if(second_flag) {
//            second_flag = 0;
//            sec++;
//            handle_Time();
//            disp_Changed();
//            ledValue = (ledValue == 0) ? 255 : 0;
//        }
//        if(buttonRB0) {
//            buttonRB0 = 0;
//            hr++;
//            handle_Time();
//            disp_Changed();
//        }
//        if(hide_flag) {
//            hide_flag = 0;
//            disp_Clock_Hide(state);
//        }
//    }
//}

void state_set_hour(void) {
    mCURSOR_LINE1;
    LCDPutStr("Set hour  RA5=->");
    disp_Clock();
    while(state == STATE_SET_HOUR) {
        LATD = ledValue;
        if(buttonRA5) {
            state = STATE_SET_MINUTE;
            buttonRA5 = 0;
            return;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            hr_changed_flag = 1;
            handle_Time();
            disp_Changed();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            hr++;
            hr_changed_flag = 1;
            handle_Time();
            disp_Changed();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}

void state_set_minute(void) {
    mCURSOR_LINE1;
    LCDPutStr("Set min   RA5=->");
    disp_Clock();
    while(state == STATE_SET_MINUTE) {
        if(buttonRA5) {
            state = STATE_SET_SECOND;
            buttonRA5 = 0;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            min_changed_flag = 1;
            handle_Time();
            disp_Changed();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            min++;
            min_changed_flag = 1;
            handle_Time();
            disp_Changed();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}

void state_set_second(void) {
    mCURSOR_LINE1;
    LCDPutStr("Set sec   RA5=->");
    disp_Clock();
    while(state == STATE_SET_SECOND) {
        if(buttonRA5) {
            state = STATE_STOP_WATCH;
            buttonRA5 = 0;
        }
        if(second_flag) {
            second_flag = 0;
            sec++;
            handle_Time();
            disp_Changed();
            ledValue = (ledValue == 0) ? 255 : 0;
        }
        if(buttonRB0) {
            buttonRB0 = 0;
            sec++;
            handle_Time();
            disp_Changed();
        }
        if(hide_flag) {
            hide_flag = 0;
            disp_Clock_Hide(state);
        }
    }
}