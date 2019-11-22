/* 
 * File:   button.h
 * Author: Tuan
 *
 * Created on November 18, 2019, 10:12 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "config.h"

#define PRESSED 0
#define RELEASE 1

#define TIME_INTERRUPT_MS 80

#define TIME_INTERVAL1_MS 600 / TIME_INTERRUPT_MS
#define TIME_INTERVAL2_MS 200 / TIME_INTERRUPT_MS
#define TIME_PRESSED1_MS 1000 / TIME_INTERRUPT_MS
#define TIME_PRESSED2_MS 3000 / TIME_INTERRUPT_MS

int readButtonRA5();
int readButtonRB0();
void handleButton(void* data_ptr);

#endif	/* BUTTON_H */

