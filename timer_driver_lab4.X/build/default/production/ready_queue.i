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
# 19 "./config.h"
typedef char tBYTE;
typedef unsigned long int tWORD;
typedef void (*FUNCTION_PTR)(void*);

typedef struct {
    tWORD delay_t;
    tWORD period_t;
    FUNCTION_PTR func_ptr;
    int next;
    void* data_p;
} task_struct;

typedef struct {
    FUNCTION_PTR func_ptr;
    void* data_p;
} queue_node;

char task_id[20] = {0};

char value = 0;

char RA5_pressed = 0;
char RB0_pressed = 0;
# 12 "./ready_queue.h" 2

queue_node ready_queue[20];
int front = -1;
int rear = -1;

void queueInitialize(void);
char enqueue(FUNCTION_PTR ptr, void* data);
queue_node dequeue();
char isEmptyQueue();
char isFullQueue();
# 2 "ready_queue.c" 2

void queueInitialize(void) {
    for(int i = 0; i< 20; i++) {
        ready_queue[i].data_p = ((void*)0);
        ready_queue[i].func_ptr = ((void*)0);
    }
}

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

char enqueue(FUNCTION_PTR ptr, void* data) {
    if(isFullQueue())
        return 0;
    if(front == -1)
        front = 0;
    rear = (rear + 1) % 20;
    ready_queue[rear].func_ptr = ptr;
    ready_queue[rear].data_p = data;
    return 1;
}

queue_node dequeue() {
    queue_node temp;
    temp.func_ptr = ((void*)0);
    temp.data_p = ((void*)0);
    if(isEmptyQueue())
        return temp;
    int idx = front;
    front = (front + 1) % 20;
    temp = ready_queue[idx];
    return temp;
}
