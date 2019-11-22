#include "FSM.h"


void IDLE_state(void) {
    if(RA5_pressed) {
        RA5_pressed = 0;
        
        state = HEATER;
        mLCD_CLEAR;
        turn_on_heater();
        turn_on_fan(1);
        LCDPrint(0, 0, "Heater");
        count_timeout = get_time();
    }
}

void HEATER_state(void) {
    if(get_time() - count_timeout >= TIME_OUT) {
        LCDPrint(0, 0, "Shutdown");
        force_turn_off();
        count_timeout = 0;
        state = IDLE;
        return;
    }
    if(flag_switch_state) {
        flag_switch_state = 0;
        
        //mLCD_CLEAR;
        LCDPrint(0, 0, "Heat Pump");
        state = HEAT_PUMP;
        count_timeout = get_time();
        turn_off_heater();
        turn_on_heat_pump();
        turn_on_fan(2);
    }
}

void HEAT_PUMP_state(void) {
    if(get_time() - count_timeout >= TIME_OUT) {
        LCDPrint(0, 0, "Shutdown");
        force_turn_off();
        count_timeout = 0;
        state = IDLE;
        return;
    }
    if(flag_switch_state) {
        flag_switch_state = 0;
        
        //mLCD_CLEAR;
        LCDPrint(0, 0, "Heater");
        count_timeout = get_time();
        state = HEATER;
        turn_off_heat_pump();
        turn_on_heater();
        turn_on_fan(1);
    }
}

void SET_TIMER_state(void) {
    
}

void changeState(void) {
    if(state != HEATER || state != HEAT_PUMP)
        return;
//    if(temperature_value >= MAX_TEMPERATURE || humidity_value <= MIN_HUMIDITY)
//        return;
    flag_switch_state = 1;
}

void check_humid_to_turn_fan(void) {
    if(state == HEATER || state == HEAT_PUMP) {
        int humid = humidity_value;
        set_speed_fan3(humid);
        LCDPrint(0, 8, "Fan3:");
        LCDPrintChar(0, 13, humid / 10);
        LCDPrintChar(0, 14, humid % 10);
    }  
}


void FSM(void) {
    switch(state) {
        case IDLE:
            if(RA5_pressed) {
                RA5_pressed = 0;

                state = HEATER;
                turn_on_heater();
                turn_on_fan(1);
                
                LCDPrint(0, 0, "Heater");
                count_timeout = get_time();
            }
            break;
        case HEATER:
            if(flag_switch_state) {
                flag_switch_state = 0;

                //mLCD_CLEAR;
                LCDPrint(0, 0, "Heat Pump");
                state = HEAT_PUMP;
                count_timeout = get_time();
                turn_off_heater();
                turn_on_heat_pump();
                turn_on_fan(2);
            }
            break;
        case HEAT_PUMP:
            if(flag_switch_state) {
                flag_switch_state = 0;

                //mLCD_CLEAR;
                LCDPrint(0, 0, "Heater");
                count_timeout = get_time();
                state = HEATER;
                turn_off_heat_pump();
                turn_on_heater();
                turn_on_fan(1);
            }
            break;
        case SET_TIMER:
            SET_TIMER_state();
            break;    
    }
}
