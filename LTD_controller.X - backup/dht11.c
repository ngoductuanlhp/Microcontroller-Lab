#include "dht11.h"

char getByte() {
    char i;
    char byteReceived = 0;
    unsigned int timeOut;
    
    for(i = 0b1000000; i != 0x00; i = i >> 1) {
        timeOut = 0xFFFF;
        while(!DHT_DATA_IN) {
            timeOut--;
            if(!timeOut) return 0;
        }
        __delay_us(40);
        if(DHT_DATA_IN) {
            byteReceived = byteReceived | i;
            timeOut = 0xFFFF;
            while(DHT_DATA_IN) {
                timeOut--;
                if(!timeOut) return 0;
            }
        }
    }
    
    return byteReceived;
}

char readDHT() {
    char checkSum;
    unsigned int timeOut = 0xFFFF;
    DHT_DIRECTION = 0;
    DHT_DATA_OUT = 1;
    __delay_ms(20);
    
    DHT_DATA_OUT = 0;
    __delay_us(60);
    DHT_DIRECTION = 1;
    
    //max 80us
    while(!DHT_DATA_IN) {
        timeOut--;
        if(!timeOut)
            return 0;
    }
    
    timeOut = 0xFFFF;
    
    //max 80us
    while(DHT_DATA_IN) {
        timeOut--;
        if(!timeOut)
            return 0;
    }

    humidity_dht11[0] = getByte();
    humidity_dht11[1] = getByte();
    temperature_dht11[0] = getByte();
    temperature_dht11[1] = getByte();
    checkSum = getByte();

    if( (char)( humidity_dht11[0] + humidity_dht11[1] + temperature_dht11[0] + temperature_dht11[1] ) != checkSum )
        return 0;

    return 1;
}

void readTempAndHumid(void) {
    if(!readDHT()) {
        temperature_value = ERROR_SENSOR_VAL;
        humidity_value = ERROR_SENSOR_VAL;
        return;
    }
    
    temperature_value = temperature_dht11[0];
    if (temperature_dht11[1] & 0x80) {
        temperature_value = -1 - temperature_value;
    }
    temperature_value += (temperature_dht11[3] & 0x0f) * 0.1;
    
    humidity_value = humidity_dht11[0]; //take 2 integral number
    //humidity_value = humidity_dht11[0] + humidity_dht11[1] * 0.1;
}