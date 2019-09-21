#include "State_Stop_Watch.h"
#include "SPI_LCD.h"

void disp_Clock_SW() {
    // Display clock on LCD Line 1
    mCURSOR_LINE2;
    LCDPutChar(min_sw/10+'0');
    LCDPutChar(min_sw%10+'0');
    LCDPutChar(':');
    LCDPutChar(sec_sw/10+'0');
    LCDPutChar(sec_sw%10+'0');
    LCDPutChar(':');
    LCDPutChar(ms_sw%10+'0'); 
}

void state_stop_watch(void) {
    mCURSOR_LINE1;
    LCDPutStr("Stop W  RA5=Next");
    disp_Clock_SW();
    LCDPutStr("        ");
    while(state == STATE_STOP_WATCH) {
        if(buttonRA5) {
            state = STATE_CLOCK;
            buttonRA5 = 0;
            state_sw = 0;
            hr_sw = 0;
            min_sw = 0;
            sec_sw = 0;
            ms_sw = 0;
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
                    ms_sw++;
                    ms_flag = 0;
                    LCDMoveCursor(1, 6);
                    LCDPutChar(ms_sw%10+'0');
                    if(ms_sw > 9) {
                        ms_sw = 0;
                        sec_sw++;
                        LCDMoveCursor(1, 6);
                        LCDPutChar(ms_sw%10+'0');
                        LCDMoveCursor(1, 3);
                        LCDPutChar(sec_sw/10+'0');
                        LCDPutChar(sec_sw%10+'0');
                    }
                    if(sec_sw > 59) {
                        sec_sw = 0;
                        min_sw++;
                        LCDMoveCursor(1, 3);
                        LCDPutChar(sec_sw/10+'0');
                        LCDPutChar(sec_sw%10+'0');
                        LCDMoveCursor(1, 0);
                        LCDPutChar(min_sw/10+'0');
                        LCDPutChar(min_sw%10+'0');
                    }
                    if(min_sw > 59) {
                        min_sw = 0;
                        LCDMoveCursor(1, 0);
                        LCDPutChar(min_sw/10+'0');
                        LCDPutChar(min_sw%10+'0');
                    }               
                }
                break;
        }
        
    }
}