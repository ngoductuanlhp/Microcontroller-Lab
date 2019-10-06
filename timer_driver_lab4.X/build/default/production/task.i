# 1 "task.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "task.c" 2
# 1 "./task.h" 1
# 11 "./task.h"
# 1 "./config.h" 1
# 17 "./config.h"
typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)();

char value = 0;
# 11 "./task.h" 2

# 1 "./ready_queue.h" 1
# 13 "./ready_queue.h"
FUNCTION_PTR ready_queue[20];
int front = -1;
int rear = -1;

char enqueue(FUNCTION_PTR ptr);
FUNCTION_PTR dequeue();
char isEmptyQueue();
char isFullQueue();
# 12 "./task.h" 2


typedef struct {
    tWORD delay_t;
    tWORD period_t;
    FUNCTION_PTR func_ptr;
    int next;
} task_struct;

task_struct task_list[20];
char num_task;
signed int head;

void initializeTaskList();
char isEmptyList();
char isFullList();
char addTask(tWORD period, tWORD delay, FUNCTION_PTR ptr);
char removeTask(char idx);
void handleListHead();
void selectReadyTask();
# 1 "task.c" 2


char isEmptyList() {
    return num_task == 0 ? 1 : 0;
}

char isFullList() {
    return num_task == 20 ? 1 : 0;
}

void initializeTaskList() {
    for(int i = 0; i < 20; i++) {
        task_list[i].delay_t = 0;
        task_list[i].period_t = 0;
        task_list[i].func_ptr = ((void*)0);
        task_list[i].next = 105;
    }
    num_task = 0;
    head = 105;
}

char addTask(tWORD period, tWORD delay, FUNCTION_PTR ptr) {
    if(isFullList())
        return 109;
    char idx;
    for(idx = 0; idx < 20; idx++) {
        if(task_list[idx].func_ptr == ((void*)0))
            break;
    }
    if(idx == 20)
        return 109;



    task_list[idx].delay_t = delay;
    task_list[idx].period_t = period;
    task_list[idx].func_ptr = ptr;
    num_task++;
    if(head == 105 || (head != 105 && task_list[head].delay_t > task_list[idx].delay_t)) {
        task_list[idx].next = head;
        head = idx;

    }
    else {
        delay = delay - task_list[head].delay_t;
        int cur = task_list[head].next;
        int prev = head;
        while(cur != 105 && task_list[cur].delay_t <= delay) {
            delay = delay - task_list[cur].delay_t;
            prev = cur;
            cur = task_list[cur].next;
        }
        task_list[prev].next = idx;
        task_list[idx].next = cur;
        task_list[idx].delay_t = delay;
    }
    if(task_list[idx].next != 105)
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
        while(task_list[pos].next != 105 && task_list[pos].next != idx) {
            pos = task_list[pos].next;
        }
        task_list[pos].next = task_list[idx].next;
        task_list[idx].next = -1;
    }

    return 1;
}

void handleListHead() {
    if(head == 105)
        return;
# 96 "task.c"
    while(task_list[head].delay_t == 0) {
        int pos = head;
        enqueue(task_list[pos].func_ptr);
        head = task_list[pos].next;
        if(task_list[pos].period_t == 0) {
            removeTask(pos);
        }
        else {
            task_list[pos].delay_t = task_list[pos].period_t;
            if(head == 105 || (head != 105 && task_list[head].delay_t > task_list[pos].delay_t)) {
                task_list[pos].next = head;
                head = pos;
            } else {
                task_list[pos].delay_t = task_list[pos].delay_t - task_list[head].delay_t;
                int cur = task_list[head].next;
                int prev = head;
                while(cur != 105 && task_list[cur].delay_t <= task_list[pos].delay_t) {
                    task_list[pos].delay_t = task_list[pos].delay_t - task_list[cur].delay_t;
                    prev = cur;
                    cur = task_list[cur].next;
                }
                task_list[prev].next = pos;
                task_list[pos].next = cur;
            }
            if(task_list[pos].next != 105)
                task_list[task_list[pos].next].delay_t = task_list[task_list[pos].next].delay_t - task_list[pos].delay_t;
        }
    }
    task_list[head].delay_t-= 10;
}

void selectReadyTask() {
    while(!isEmptyQueue()) {
        FUNCTION_PTR ptr = dequeue();
        if( ptr != ((void*)0))
            (ptr)();
    }
}
