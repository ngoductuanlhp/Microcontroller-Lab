#include "dht11.h"

char getByte() {
    char i, j;
    unsigned int timeOut;
    for(j = 0; j < 8; j++){
        while(!DHT_DATA_IN) //Wait until PORTD.F0 goes HIGH
            if(--timeOut == 0) return 0;
         __delay_us(30);
        if(DHT_DATA_IN == 0)
            i&= ~(1<<(7 - j)); //Clear bit (7-b)
        else {
            i|= (1 << (7 - j)); //Set bit (7-b)
            timeOut = TIME_OUT_DHT;
            while(DHT_DATA_IN)
                if(--timeOut == 0) return 0;
        } //Wait until PORTD.F0 goes LOW
    }
    return i;
}

char readDHT() {
    
    char checkSum;
    unsigned int timeOut = TIME_OUT_DHT;
    DHT_DIRECTION = 0;
    DHT_DATA_OUT = 0;
    __delay_ms(20);
    
    DHT_DATA_OUT = 1;
    __delay_us(20);
    DHT_DIRECTION = 1;
    
    while(DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }
    
    
    timeOut = TIME_OUT_DHT;
    while(!DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }
    
    timeOut = TIME_OUT_DHT;
    while(DHT_DATA_IN & 1) {
        if(--timeOut == 0)
            return 0;
    }

    humidity_dht11[0] = getByte();
    humidity_dht11[1] = getByte();
    temperature_dht11[0] = getByte();
    temperature_dht11[1] = getByte();
    checkSum = getByte();
//    LCDPrintChar(1, 0, temperature_dht11[0] / 10 + '0');
//    LCDPrintChar(1, 1, temperature_dht11[0] % 10 + '0');
//    LCDPrintChar(1, 2, temperature_dht11[1] / 10 + '0');
//    LCDPrintChar(1, 3, temperature_dht11[1] % 10 + '0');
//    LCDPrintChar(1, 4, humidity_dht11[0] / 10 + '0');
//    LCDPrintChar(1, 5, humidity_dht11[0] % 10 + '0');
//    LCDPrintChar(1, 6, humidity_dht11[1] / 10 + '0');
//    LCDPrintChar(1, 7, humidity_dht11[1] % 10 + '0');
//    LCDPrintChar(1, 8, checkSum / 10 + '0');
//    LCDPrintChar(1, 9, checkSum % 10 + '0');
//    char test = (humidity_dht11[0] + humidity_dht11[1] + temperature_dht11[0] + temperature_dht11[1]) & 0xFF;
//    LCDPrintChar(1, 10, test / 10 + '0');
//    LCDPrintChar(1, 11, test % 10 + '0');
    if( (char)( humidity_dht11[0] + humidity_dht11[1] + temperature_dht11[0] + temperature_dht11[1] ) & 0xFF != checkSum )
        return 0;
    return 1;
}

void readTempAndHumid(void) {
    if(!readDHT()) {
        //LCDPrint(1, 8, "ERROR");
        temperature_value = ERROR_SENSOR_VAL;
        humidity_value = ERROR_SENSOR_VAL;
        return;
    }
    
    temperature_value = temperature_dht11[0];
    humidity_value = humidity_dht11[0];
//    if(!readDHT()) {
//        temperature_value = ERROR_SENSOR_VAL;
//        humidity_value = ERROR_SENSOR_VAL;
//        return;
//    }
    
//    temperature_value = temperature_dht11[0];
//    if (temperature_dht11[1] & 0x80) {
//        temperature_value = -1 - temperature_value;
//    }
//    temperature_value += (temperature_dht11[3] & 0x0f) * 0.1;
//    
//    humidity_value = humidity_dht11[0]; //take 2 integral number
    //humidity_value = humidity_dht11[0] + humidity_dht11[1] * 0.1;
}
