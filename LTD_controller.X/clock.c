#include "clock.h"

//Ready queue tasks
queue_node ready_queue[MAX_SIZE];
int front = -1;
int rear = -1;

void queueInitialize(void) {
    for(int i = 0; i< MAX_SIZE; i++) {
        ready_queue[i].data_p = ((void*)0);
        ready_queue[i].func_ptr = ((void*)0);
    }
}

char getSizeQueue() {
    return (rear - front + 1 + MAX_SIZE) % MAX_SIZE;
}

char isFullQueue() {
    return getSizeQueue() >= MAX_SIZE ? 1 : 0;
}

char isEmptyQueue() {
    if(front == -1)
        return 0;
    return getSizeQueue() == 0 ? 1 : 0;
}

char enqueue(FUNCTION_PTR ptr, void* data_ptr) {
    if(isFullQueue())
        return 0;
    if(front == -1)
        front = 0;
    rear = (rear + 1) % MAX_SIZE;
    ready_queue[rear].func_ptr = ptr;
    ready_queue[rear].data_p = data_ptr;
    return 1;
}

queue_node dequeue() {
    queue_node temp;
    temp.func_ptr = ((void*)0);
    temp.data_p = ((void*)0);
    if(isEmptyQueue())
        return temp;
    int idx = front;
    front = (front + 1) % MAX_SIZE;
    temp = ready_queue[idx];
    return temp;
}
//------------------------------------------------------------------------------

//List of tasks in system
task_struct task_list[MAX_SIZE];
char num_task;
char head;

int count = 0;

void initializeTaskList() {
    queueInitialize();
    for(int i = 0; i < MAX_SIZE; i++) {
        task_list[i].delay_t = 0;
        task_list[i].period_t = 0;
        task_list[i].func_ptr = ((void*)0);
        task_list[i].data_p = ((void*)0);
        task_list[i].next = NULL_VAL;
    }
    num_task = 0;
    head = NULL_VAL;
}

char isEmptyList() {
    return num_task == 0 ? 1 : 0;
}

char isFullList() {
    return num_task == MAX_SIZE ? 1 : 0;
}
//------------------------------------------------------------------------------


int start_timer(char timer_vaddr) {
    if(timer_vaddr > 4) 
        return 0;
    switch(timer_vaddr) {
        case 0:
            INTCONbits.TMR0IE = 1;
            INTCONbits.TMR0IF = 0;
            T0CON = 0xC3;
            TMR0L = TMR0_PRELOAD;// 1ms interrupt
            time_ms = 0;
            break;
        case 1:
            initializeTaskList();
            PIE1bits.TMR1IE = 1;
            PIR1bits.TMR1IF = 0;
            T1CON = 0b10000001;
            TMR1H = TMR1H_PRELOAD;
            TMR1L = TMR1L_PRELOAD;//10ms interrupt
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
    return 1;   
}

unsigned long int get_time(void) {
    return time_ms;
}

char register_timer(tWORD period, tWORD delay, FUNCTION_PTR callback, void *data_ptr) {
    if(isFullList())
        return ERROR_VAL;            
    char idx;
    for(idx = 0; idx < MAX_SIZE; idx++) {
        if(task_list[idx].func_ptr == ((void*)0))
            break;
    }
    if(idx == MAX_SIZE)
        return ERROR_VAL;
    task_list[idx].delay_t = delay;
    task_list[idx].period_t = period;
    task_list[idx].func_ptr = callback;
    task_list[idx].data_p = data_ptr;
    num_task++;
    int sum = task_list[head].delay_t;
    if(head == NULL_VAL || (head != NULL_VAL && sum > delay)) {
        task_list[idx].next = head;
        head = idx;
    }
    else {
        //delay -= sum;
        int cur = task_list[head].next;
        int prev = head;
        while(cur != NULL_VAL && sum + task_list[cur].delay_t <= delay) {
            //delay -= task_list[cur].delay_t; 
            sum+= task_list[cur].delay_t;
            prev = cur;
            cur = task_list[cur].next;
        }
        task_list[prev].next = idx;
        task_list[idx].next = cur;
        task_list[idx].delay_t = delay - sum;
    }
    if(task_list[idx].next != NULL_VAL)
        task_list[task_list[idx].next].delay_t-= task_list[idx].delay_t;
    return idx;
}

int remove_timer(char id) {
    if(isEmptyList() || task_list[id].func_ptr == ((void*)0))
        return 0;
    task_list[id].delay_t = 0;
    task_list[id].period_t = 0;
    task_list[id].func_ptr = ((void*)0);
    task_list[id].data_p = ((void*)0);
    num_task--;
    if(id == head) {
        head = task_list[id].next;
        task_list[id].next = NULL_VAL;
    }
    else {
        char pos = head;
        while(task_list[pos].next != NULL_VAL && task_list[pos].next != id) {
            pos = task_list[pos].next;
        }
        task_list[pos].next = task_list[id].next;
        task_list[id].next = NULL_VAL;
    }   
    return 1;
}

int stop_timer(void) {
    INTCONbits.TMR0IE = 0;
    INTCONbits.TMR0IF = 0;
    PIE1bits.TMR1IE = 0;
    PIR1bits.TMR1IF = 0;
    time_ms = 0;
    return 0;
}

void __interrupt() timer_interrupt(void) {
    if(INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = TMR0_PRELOAD;
        time_ms++;
    }
    if(PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = TMR1H_PRELOAD;
        TMR1L = TMR1L_PRELOAD;
        if(head == NULL_VAL)
            return;
        while(task_list[head].delay_t == 0) {
            int pos = head;
            enqueue(task_list[pos].func_ptr, task_list[pos].data_p);       
            head = task_list[pos].next;
            if(task_list[pos].period_t == 0) {
                remove_timer(pos);
            }
            else {
                task_list[pos].delay_t = task_list[pos].period_t;
                int sum = task_list[head].delay_t;
                if(head == NULL_VAL || (head != NULL_VAL && sum > task_list[pos].delay_t)) {
                    task_list[pos].next = head;
                    head = pos;
                } else {
                    //task_list[pos].delay_t = task_list[pos].delay_t - task_list[head].delay_t;
                    int cur = task_list[head].next;
                    int prev = head;
                    while(cur != NULL_VAL && sum + task_list[cur].delay_t <= task_list[pos].delay_t) {
                        //task_list[pos].delay_t -= task_list[cur].delay_t;
                        sum+= task_list[cur].delay_t;
                        prev = cur;
                        cur = task_list[cur].next;
                    }
                    task_list[prev].next = pos;
                    task_list[pos].next = cur;
                    task_list[pos].delay_t-= sum;
                }
                if(task_list[pos].next != NULL_VAL)
                    task_list[task_list[pos].next].delay_t -= task_list[pos].delay_t;
            }
        }
        task_list[head].delay_t-= INTERRUPT_INTERVAL;
    }
}

void dispatch(void) {
    while(!isEmptyQueue()) {
        queue_node node = dequeue();
        if(node.func_ptr != ((void*)0))
            (node.func_ptr)(node.data_p);
    }
}

