#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int a[] = {34, 213, 75,  123, 678, 223, 56,   22, 67, 34,  987, 234, 52, 72,  87,
           34, 67,  784, 154, 968, 134, 7687, 16, 56, 125, 635, 7,   44, 594, 488};
double b[] = {10.67, 5.292, 2.986, 1.553, 4.900, 2.755, 7.741, 10.99, 9.786, 2.378,
              10.33, 9.072, 6.087, 7.006, 3.235, 5.241, 6.605, 6.748, 3.629, 10.03};

#define cmp_func(size)                                                                             \
    int cmp_##size(const void *_a, const void *_b) /*参数格式固定*/                          \
    {                                                                                              \
        size a = *(size *)_a; /*强制类型转换*/                                               \
        size b = *(size *)_b;                                                                      \
        if (a != b)                                                                                \
            return a > b ? 1 : -1;                                                                 \
        return 0;                                                                                  \
    }

// 宏定义式比较函数
// 用法：参数为简单类型名，如 int，double，生成对应的比较函数，复杂的类型需要自己写
cmp_func(int);
// 等价于
// int cmp_int(const void *_a, const void *_b) {
//     int a = *(int *)_a;
//     int b = *(int *)_b;
//     if (a != b)
//         return a > b ? 1 : -1;
//     return 0;
// }

cmp_func(double);
int main() {
    qsort(a, sizeof a / sizeof(int), sizeof a[0], cmp_int);
    for (int i = 0; i < sizeof a / sizeof(int); i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    qsort(b, sizeof b / sizeof(double), sizeof b[0], cmp_double);
    for (int i = 0; i < sizeof b / sizeof(double); i++) {
        printf("%.2lf ", b[i]);
    }
    return 0;
}