#include <stdio.h>
#include <stdlib.h>

// 栈的大小
const size_t MAX_SIZE = 2000;

// 栈的元素类型，可以根据需要修改，此处为 int，下面有一些注释掉的例子
typedef int ele;
// typedef double ele;
/* typedef struct {
    int op;
    char s[10];
} ele; */

typedef struct {
    ele *bottom, *top;
} stack, *pStack;
// 创建新栈，大小为 MAX_SIZE，返回栈的指针
pStack new_stack() {
    pStack s = (pStack)malloc(sizeof(stack));
    s->bottom = (ele *)malloc(sizeof(ele) * MAX_SIZE);
    s->top = s->bottom;
    init_stack(s);
    return s;
}
// 入栈，将 x 压入栈 s 中
void push(pStack s, ele x) {
    *(s->top) = x;
    s->top++;
}
// 出栈，返回栈 s 的栈顶元素
ele pop(pStack s) {
    s->top--;
    return *(s->top);
}
// 判断栈 s 是否为空，若为空返回 1，否则返回 0
int is_empty(pStack s) {
    return s->top == s->bottom;
}
// 返回栈 s 的栈顶元素
ele top(pStack s) {
    return *(s->top - 1);
}
// 释放栈 s 的空间，考试时不需要写
void free_stack(pStack s) {
    free(s->bottom);
    free(s);
}

int main() {
    pStack s = new_stack();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);
    while (!is_empty(s)) {
        printf("%d ", pop(s));
    }
    free_stack(s);
    return 0;
}