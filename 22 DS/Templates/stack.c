#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 2000;

// 栈的元素类型，可以自行修改
typedef int ele;
/* typedef struct {
    int x;
    int y;
} ele; */

typedef struct {
    int top;
    ele *bottom;
} stack, *pStack;
// 创建一个栈，返回栈的指针
pStack new_stack() {
    pStack s = (pStack)malloc(sizeof(stack));
    s->bottom = (ele *)malloc(sizeof(ele) * MAX_SIZE);
    s->top = 0;
    return s;
}
// 判断栈是否为空
int is_empty(pStack s) {
    return s->top == 0;
}
// 判断栈是否已满
int is_full(pStack s) {
    return s->top == MAX_SIZE;
}
// 压入元素
void push(pStack s, ele x) {
    if (is_full(s)) {
        printf("Stack is full!");
        return;
    }
    s->bottom[s->top++] = x;
}
// 弹出栈顶元素
ele pop(pStack s) {
    if (is_empty(s)) {
        printf("Stack is empty!");
        exit(1); // or return a special ele value
    }
    return s->bottom[--s->top];
}
// 返回栈顶元素，不弹出
ele top(pStack s) {
    return s->bottom[s->top - 1];
}
// 释放栈空间，考试时不用写
void free_stack(pStack s) {
    free(s->bottom);
    free(s);
}

int main() {
    pStack s = new_stack();
    for (int i = 0; i < 10; i++) {
        push(s, i);
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", pop(s));
    }
    free_stack(s);
    return 0;
}