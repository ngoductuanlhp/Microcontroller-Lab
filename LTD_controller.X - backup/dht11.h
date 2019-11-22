/* 
 * File:   dht11.h
 * Author: Tuan
 *
 * Created on November 4, 2019, 10:13 AM
 */

#ifndef DHT11_H
#define	DHT11_H

#include "config.h"

#define DHT_DATA_IN PORTCbits.RC3
#define DHT_DATA_OUT LATCbits.LC3
#define DHT_DIRECTION TRISCbits.RC3

char temperature_dht11[2];
char humidity_dht11[2];

void readTempAndHumid(void);

#endif	/* DHT11_H */

