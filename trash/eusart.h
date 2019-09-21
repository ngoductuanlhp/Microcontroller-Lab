/* 
 * File:   eusart.h
 * Author: Tuan
 *
 * Created on September 16, 2019, 10:03 PM
 */

#ifndef EUSART_H
#define	EUSART_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void eusart_init();
uint8_t EUSART1_Read(void);
void EUSART1_Write(uint8_t txData);
char getch(void);
void putch(char txData);

#endif	/* EUSART_H */

