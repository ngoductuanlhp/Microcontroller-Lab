#include "State_Stop_Watch.h"
#include "SPI_LCD.h"

void disp_Changed_SW(void) {
    if(ms_sw_changed_flag) {
        ms_sw_changed_flag = 0;
        LCDMoveCursor(1, 6);
        LCDPutChar(ms_sw/10+'0');
        LCDPutChar(ms_sw%10+'0');
    }
    if(sec_sw_changed_flag) {
        sec_changed_flag = 0;
        LCDMoveCursor(1, 3);
        LCDPutChar(sec_sw/10+'0');
        LCDPutChar(sec_sw%10+'0');
    }
    if(min_sw_changed_flag) {
        min_changed_flag = 0;
        LCDMoveCursor(1, 0);
        LCDPutChar(min_sw/10+'0');
        LCDPutChar(min_sw%10+'0');
    }
}

void handle_Time_SW(void) {
    ms_sw_changed_flag = 1;
    if (ms_sw > 99) {
        ms_sw = 0;
        sec_sw++;
        sec_sw_changed_flag = 1;
    }
    if (sec_sw > 59) {
        sec_sw = 0;                // Set minutes to 0
        min_sw ++;                   // Increment hours
        min_sw_changed_flag = 1;
    }
    if (min_sw  > 59) {
        min_sw  = 0;                     // Set hour to 1
    }
}

void disp_Clock_SW() {
    // Display clock on LCD Line 1
    mCURSOR_LINE2;
    LCDPutChar(min_sw/10+'0');
    LCDPutChar(min_sw%10+'0');
    LCDPutChar(':');
    LCDPutChar(sec_sw/10+'0');
    LCDPutChar(sec_sw%10+'0');
    LCDPutChar(':');
    LCDPutChar(ms_sw/10+'0');
    LCDPutChar(ms_sw%10+'0'); 
}

void state_stop_watch(void) {
    mCURSOR_LINE1;
    LCDPutStr("Stop W    RA5=->");
    disp_Clock_SW();
    LCDPutStr("        ");
    while(state == STATE_STOP_WATCH) {
        LATD = ledValue;
        if(buttonRA5) {
            state = STATE_CLOCK;
            buttonRA5 = 0;
            state_sw = 0;
            min_sw = 0;
            sec_sw = 0;
            ms_sw = 0;
        }
        if(second_flag == 1) {
            second_flag = 0;
            sec++;
            handle_Time();
            ledValue = (ledValue == 0) ? 255 : 0;        
        }
        switch(state_sw) {
            case 0:
                if(buttonRB0) {
                    buttonRB0 = 0;
                    state_sw = 1;
                }
                break;
            case 1:
                if(buttonRB0) {
                    buttonRB0 = 0;
                    state_sw = 0;
                }
                if(ms_flag) {
                    ms_flag = 0;
                    ms_sw++;
                    handle_Time_SW();
                    disp_Changed_SW();      
                }
                break;
        }
        
    }
}