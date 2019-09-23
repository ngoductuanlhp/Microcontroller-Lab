/* 
 * File:   buttons.h
 * Author: Tuan
 *
 * Created on September 16, 2019, 9:05 AM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

typedef unsigned char tBYTE;
typedef unsigned int tWORD;

tBYTE firstReadRA5 = 1;
tBYTE secondReadRA5 = 1;
tBYTE firstReadRB0 = 1;
tBYTE secondReadRB0 = 1;

tWORD countRA5_1 = 0;
tWORD countRA5_2 = 0;

tWORD countRB0_1 = 0;
tWORD countRB0_2 = 0;

int readButtonRA5();
int readButtonRB0();
void handleButton();

#endif	/* BUTTONS_H */

