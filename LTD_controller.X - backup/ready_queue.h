/* 
 * File:   ready_queue.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 10:02 PM
 */

#ifndef READY_QUEUE_H
#define	READY_QUEUE_H

#include "config.h"

queue_node ready_queue[MAX_SIZE];
int front = -1;
int rear = -1;

void queueInitialize(void);
char enqueue(FUNCTION_PTR ptr, void* data_ptr);
queue_node dequeue();
char isEmptyQueue();
char isFullQueue();

#endif	/* READY_QUEUE_H */

