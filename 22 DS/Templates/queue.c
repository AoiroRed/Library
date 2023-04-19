#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 2000;
// 队列的元素类型，可以自行修改
typedef int ele;
/* typedef struct {
    int x;
    int y;
} ele; */

typedef struct {
    int front, rare;
    ele *ele;
} Queue, *pQueue;
// 创建一个队列，返回队列指针
pQueue new_queue() {
    pQueue q = (pQueue)malloc(sizeof(Queue));
    q->ele = (ele *)malloc(MAX_SIZE * sizeof(ele));
    q->front = q->rare = 0;
    return q;
}
// 判断队列是否为空
int is_empty(pQueue q) {
    return q->front == q->rare;
}
// 判断队列是否已满
int is_full(pQueue q) {
    return (q->rare + 1) % MAX_SIZE == q->front;
}
// 入队
void enqueue(pQueue q, ele e) {
    if (is_full(q)) {
        printf("Queue is full!");
        return;
    }
    q->ele[q->rare] = e;
    q->rare = (q->rare + 1) % MAX_SIZE;
}
// 出队
ele dequeue(pQueue q) {
    if (is_empty(q)) {
        printf("Queue is empty!");
        exit(1); // or return a special ele value
    }
    ele e = q->ele[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return e;
}
// 释放队列空间，考试时不用写
void free_queue(pQueue q) {
    free(q->ele);
    free(q);
}

int main() {
    pQueue q = new_queue();
    for (int i = 0; i < 10; i++) {
        enqueue(q, i);
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", dequeue(q));
    }
    free_queue(q);
    return 0;
}
