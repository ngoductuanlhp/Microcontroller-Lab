/* 
 * File:   task.h
 * Author: Tuan
 *
 * Created on October 5, 2019, 10:07 PM
 */

#ifndef TASK_H
#define	TASK_H

#include "config.h"
#include "ready_queue.h"

//typedef struct {
//    tWORD delay_t;
//    tWORD period_t;
//    FUNCTION_PTR func_ptr;
//    int next;
//    void* data_p;
//} task_struct;

task_struct task_list[MAX_SIZE];
char num_task;
signed int head;

void initializeTaskList();
char isEmptyList();
char isFullList();
char addTask(tWORD period, tWORD delay, FUNCTION_PTR ptr, void *data);
char removeTask(char idx);
void handleListHead();
void selectReadyTask();

#endif	/* TASK_H */

