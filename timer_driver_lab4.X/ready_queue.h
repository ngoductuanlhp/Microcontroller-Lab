/* 
 * File:   ready_queue.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 10:02 PM
 */

#ifndef READY_QUEUE_H
#define	READY_QUEUE_H

#include "config.h"

FUNCTION_PTR ready_queue[MAX_SIZE];
int front = -1;
int rear = -1;

char enqueue(FUNCTION_PTR ptr);
FUNCTION_PTR dequeue();
char isEmptyQueue();
char isFullQueue();

#endif	/* READY_QUEUE_H */

