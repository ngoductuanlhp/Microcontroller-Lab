/* 
 * File:   interrupt_manager.h
 * Author: Tuan
 *
 * Created on September 16, 2019, 8:53 AM
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

void interrupt_init();
void __interrupt() myISR(void);


#endif	/* INTERRUPT_MANAGER_H */

