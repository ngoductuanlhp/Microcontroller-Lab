/* 
 * File:   dht11.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:25 AM
 */

#ifndef DHT11_H
#define	DHT11_H

#include "config.h"
#include "lcd.h"

#define TIME_OUT_DHT 80

#define DHT_DATA_IN PORTDbits.RD0
#define DHT_DATA_OUT LATDbits.LATD0
#define DHT_DIRECTION TRISDbits.TRISD0

char temperature_dht11[2];
char humidity_dht11[2];

void readTempAndHumid(void);

#endif	/* DHT11_H */

