#include "ready_queue.h"

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

char enqueue(FUNCTION_PTR ptr) {
    if(isFullQueue())
        return 0;
    if(front == -1)
        front = 0;
    rear = (rear + 1) % MAX_SIZE;
    ready_queue[rear] = ptr;
    return 1;
}

FUNCTION_PTR dequeue() {
    if(isEmptyQueue())
        return ((void*)0);
    int idx = front;
    front = (front + 1) % MAX_SIZE;
    return ready_queue[idx];
}
