#include "task.h"

char isEmptyList() {
    return num_task == 0 ? 1 : 0;
}

char isFullList() {
    return num_task == MAX_SIZE ? 1 : 0;
}

void initializeTaskList() {
    for(int i = 0; i < MAX_SIZE; i++) {
        task_list[i].delay_t = 0;
        task_list[i].period_t = 0;
        task_list[i].func_ptr = ((void*)0);
        task_list[i].next = NULL_VAL;
    }
    num_task = 0;
    head = NULL_VAL;
}

char addTask(tWORD period, tWORD delay, FUNCTION_PTR ptr) {
    if(isFullList())
        return ERROR_VAL;
    char idx;
    for(idx = 0; idx < MAX_SIZE; idx++) {
        if(task_list[idx].func_ptr == ((void*)0))
            break;
    }
    if(idx == MAX_SIZE)
        return ERROR_VAL;
//    char idx = num_task;
//    while(task_list[idx].func_ptr != ((void*)0))
//        idx = (idx + 1) % MAX_SIZE;
    task_list[idx].delay_t = delay;
    task_list[idx].period_t = period;
    task_list[idx].func_ptr = ptr;
    num_task++;
    if(head == NULL_VAL || (head != NULL_VAL && task_list[head].delay_t > task_list[idx].delay_t)) {
        task_list[idx].next = head;
        head = idx;
        //value =0xFF;
    }
    else {
        delay = delay - task_list[head].delay_t;
        int cur = task_list[head].next;
        int prev = head;
        while(cur != NULL_VAL && task_list[cur].delay_t <= delay) {
            delay = delay - task_list[cur].delay_t; 
            prev = cur;
            cur = task_list[cur].next;    
        }
        task_list[prev].next = idx;
        task_list[idx].next = cur;
        task_list[idx].delay_t = delay;
    }
    if(task_list[idx].next != NULL_VAL)
        task_list[task_list[idx].next].delay_t = task_list[task_list[idx].next].delay_t - delay;
    return idx;
}

char removeTask(char idx) {
    if(isEmptyList() || task_list[idx].func_ptr == ((void*)0))
        return 0;
    task_list[idx].delay_t = 0;
    task_list[idx].period_t = 0;
    task_list[idx].func_ptr = ((void*)0);
    num_task--;
    if(idx == head) {
        head = task_list[idx].next;
        task_list[idx].next = -1;
    }
    else {
        char pos = head;
        while(task_list[pos].next != NULL_VAL && task_list[pos].next != idx) {
            pos = task_list[pos].next;
        }
        task_list[pos].next = task_list[idx].next;
        task_list[idx].next = -1;
    }
    
    return 1;
}

void handleListHead() {
    if(head == NULL_VAL)
        return;
    //value =0x01;
    //task_list[head].delay_t-= INTERRUPT_INTERVAL;
//    if(task_list[head].delay_t == 0) {
//        //value =0x03;
//        enqueue(task_list[head].func_ptr);
//        task_list[head].delay_t = task_list[head].period_t;
//    }
//    task_list[head].delay_t-= INTERRUPT_INTERVAL;
    while(task_list[head].delay_t == 0) {
        int pos = head;
        enqueue(task_list[pos].func_ptr);       
        head = task_list[pos].next;
        if(task_list[pos].period_t == 0) {
            removeTask(pos);
        }
        else {
            task_list[pos].delay_t = task_list[pos].period_t;
            if(head == NULL_VAL || (head != NULL_VAL && task_list[head].delay_t > task_list[pos].delay_t)) {
                task_list[pos].next = head;
                head = pos;
            } else {
                task_list[pos].delay_t = task_list[pos].delay_t - task_list[head].delay_t;
                int cur = task_list[head].next;
                int prev = head;
                while(cur != NULL_VAL && task_list[cur].delay_t <= task_list[pos].delay_t) {
                    task_list[pos].delay_t = task_list[pos].delay_t - task_list[cur].delay_t;
                    prev = cur;
                    cur = task_list[cur].next;
                }
                task_list[prev].next = pos;
                task_list[pos].next = cur;
            }
            if(task_list[pos].next != NULL_VAL)
                task_list[task_list[pos].next].delay_t =  task_list[task_list[pos].next].delay_t - task_list[pos].delay_t;
        }
    }
    task_list[head].delay_t-= INTERRUPT_INTERVAL;
}

void selectReadyTask() {
    while(!isEmptyQueue()) {
        FUNCTION_PTR ptr = dequeue();
        if( ptr != ((void*)0))
            (ptr)();
    }
}
