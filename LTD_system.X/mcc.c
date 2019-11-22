#include "mcc.h"

void osc_initialize(void) {
    OSCCON = 0x70; //Fosc = 8MHz
}

void pin_initialize(void) {
    LATC = 0x00;
    TRISC = 0xD7;
    ADCON1 = 0b00001111;
    
    LATA = 0x00;
    TRISA = 0xF3;
//    ANSELA = 0x0B;

    LATB = 0x00;
    TRISB = 0xFF;
    
    //LED
    LATD = 0x00;
    TRISD = 0x00;
}

void PWM_initialize(void) {
    TRISGbits.RG3 = 0; //CCP4
    TRISGbits.RG4 = 0; //CCP5
    PR2 = 249; //period = 2ms
    T2CON = 0x03;//prescale = 16
    CCP4CON = 0b00001100;
    CCPR4L = 0x00;
    TMR2 = 0;
    T2CONbits.TMR2ON = 1;
}

void interrupt_initialize(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}


void system_initialize(void) {
    osc_initialize();
    pin_initialize();
    interrupt_initialize();
    mOPEN_LCD;
    humidity_value = 70;
    temperature_value = 25;
    start_timer(0);//for timestamp
    start_timer(1);//for handle tasks
}

void changeState(void) {
    if(temperature_value >= MAX_TEMPERATURE && humidity_value <= MIN_HUMIDITY && state != IDLE)
        state = TERMINATE;
    else if(humidity_value <= MIN_HUMIDITY && state == HEAT_PUMP) {
        flag_change_state = 1;
    }
    else if(temperature_value >= MAX_TEMPERATURE && state == HEATER)
        flag_change_state = 1;
    else if(state == HEATER || state == HEAT_PUMP)
        flag_change_state = 1;
     
}

void check_humid_to_turn_fan(void) {
    if(state == HEATER || state == HEAT_PUMP) {
        int humid = (int)humidity_value;
        set_speed_fan3(humid);
        LCDPrint(1, 11, "F3:");
        LCDPrintChar(1, 14, humid / 10 + '0');
        LCDPrintChar(1, 15, humid % 10 + '0');
    }  
}

void print_temp_and_humid(void) {
    LCDPrint(1, 0, "T:");
    LCDPrint(1, 6, "H:");
    if(temperature_value == ERROR_SENSOR_VAL) {
        LCDPrint(1, 3, "ER");
    } else{
        LCDPrintChar(1, 3, temperature_value / 10 + '0');
        LCDPrintChar(1, 4, temperature_value % 10 + '0');
    }
    if(humidity_value == ERROR_SENSOR_VAL) {
        LCDPrint(1, 8, "ER");
    } else {
        LCDPrintChar(1, 8, humidity_value / 10 + '0');
        LCDPrintChar(1, 9, humidity_value % 10 + '0');
    }
}
