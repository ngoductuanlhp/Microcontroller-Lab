# 1 "ready_queue.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ready_queue.c" 2
# 1 "./ready_queue.h" 1
# 11 "./ready_queue.h"
# 1 "./config.h" 1
# 17 "./config.h"
typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)();

typedef struct {
    tWORD delay_t;
    tWORD period_t;
    FUNCTION_PTR func_ptr;
    int next;
    void* data_p;
} task_struct;

char value = 0;
# 11 "./ready_queue.h" 2


FUNCTION_PTR ready_queue[20];
int front = -1;
int rear = -1;

char enqueue(FUNCTION_PTR ptr);
FUNCTION_PTR dequeue();
char isEmptyQueue();
char isFullQueue();
# 1 "ready_queue.c" 2


char getSizeQueue() {
    return (rear - front + 1 + 20) % 20;
}

char isFullQueue() {
    return getSizeQueue() >= 20 ? 1 : 0;
}

char isEmptyQueue() {
    if(front == -1)
        return 0;
    return getSizeQueue() == 0 ? 1 : 0;
}

char enqueue(FUNCTION_PTR ptr) {
    if(isFullQueue())
        return 0;
    if(front == -1)
        front = 0;
    rear = (rear + 1) % 20;
    ready_queue[rear] = ptr;
    return 1;
}

FUNCTION_PTR dequeue() {
    if(isEmptyQueue())
        return ((void*)0);
    int idx = front;
    front = (front + 1) % 20;
    return ready_queue[idx];
}
