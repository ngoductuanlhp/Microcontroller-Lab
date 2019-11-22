//#include "ready_queue.h"
//
//void queueInitialize(void) {
//    for(int i = 0; i< MAX_SIZE; i++) {
//        ready_queue[i].data_p = ((void*)0);
//        ready_queue[i].func_ptr = ((void*)0);
//    }
//}
//
//char getSizeQueue() {
//    return (rear - front + 1 + MAX_SIZE) % MAX_SIZE;
//}
//
//char isFullQueue() {
//    return getSizeQueue() >= MAX_SIZE ? 1 : 0;
//}
//
//char isEmptyQueue() {
//    if(front == -1)
//        return 0;
//    return getSizeQueue() == 0 ? 1 : 0;
//}
//
//char enqueue(FUNCTION_PTR ptr, void* data_ptr) {
//    if(isFullQueue())
//        return 0;
//    if(front == -1)
//        front = 0;
//    rear = (rear + 1) % MAX_SIZE;
//    ready_queue[rear].func_ptr = ptr;
//    ready_queue[rear].data_p = data_ptr;
//    return 1;
//}
//
//queue_node dequeue() {
//    queue_node temp;
//    temp.func_ptr = ((void*)0);
//    temp.data_p = ((void*)0);
//    if(isEmptyQueue())
//        return temp;
//    int idx = front;
//    front = (front + 1) % MAX_SIZE;
//    temp = ready_queue[idx];
//    return temp;
//}
