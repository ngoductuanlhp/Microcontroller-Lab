#include "State_Set.h"
#include "State_Clock.h"
#include "SPI_LCD.h"

void state_set_hour(void) {
    if(changed_state_flag) {
        changed_state_flag = 0;
        mCURSOR_LINE1;
        LCDPutStr("Set hour  RA5=->");
        disp_Clock();
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

void state_set_minute(void) {
    if(changed_state_flag) {
        changed_state_flag = 0;
        mCURSOR_LINE1;
        LCDPutStr("Set min   RA5=->");
        disp_Clock();
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

void state_set_second(void) {
    if(changed_state_flag) {
        changed_state_flag = 0;
        mCURSOR_LINE1;
        LCDPutStr("Set sec   RA5=->");
        disp_Clock();
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