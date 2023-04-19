#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK
#define QUEUE

// typedef int ele;
typedef char *ele;

// return 1 if a > b, -1 if a < b, 0 if a == b
int equal_ele(ele a, ele b);
// copy the value of src to dest
void copy_ele(ele *dest, ele src);
// print the value of val
void print_ele(ele val);

// int equal_ele(ele a, ele b) {
//     return a == b;
// }
// void copy_ele(ele *dest, ele src) {
//     *dest = src;
// }
// void print_ele(ele val) {
//     printf("%d ", val);
// }

int equal_ele(ele a, ele b) {
    return strcmp(a, b);
}
void copy_ele(ele *dest, ele src) {
    *dest = (char *)malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(*dest, src);
}
void print_ele(ele val) {
    printf("%s ", val);
}

typedef struct node {
    ele val;
    struct node *next, *prev;
} Node, *pNode;

pNode new_node(ele);

typedef struct {
    pNode head, tail;
    int size;
} List, *pList;

// Iterate over the elements in the list named "list".
// During the loop, assign the list elements to the variable "node"
// Note: you can't remove the current node in the loop
#define list_for_each(list, node) for (pNode node = list->head; node != NULL; node = node->next)

// Iterate over the elements in the list named "list" in reverse order.
#define list_for_each_reverse(list, node)                                                          \
    for (pNode node = list->tail; node != NULL; node = node->prev)

// Iterate over the elements in the list named "list" from the node "node".
#define list_for_each_from(list, node) for (; node != NULL; node = cycle_next(list, node))

// Iterate over the elements in the list named "list" from the node "node" in reverse order.
#define list_for_each_from_reverse(list, node) for (; node != NULL; node = cycle_prev(list, node))

// Iterate over the elements in the list named "list".
// Note: you can remove the node in the loop,
//       but you can't remove the next node of the current node
#define list_for_each_safe(list, node, next)                                                       \
    for (pNode node = list->head, next = node == NULL ? NULL : node->next; node != NULL;           \
         node = next, next = node == NULL ? NULL : node->next)

pList new_list();
pList new_list_from_array(ele *, int);

pNode get_head(pList);
pNode get_tail(pList);
pNode find(pList, ele);
pNode find_k(pList, ele, int);
pNode find_at(pList, int);
pNode find_eq(pList, ele, int (*)(ele, ele));

void insert_tail(pList, ele);
void insert_head(pList, ele);
void insert_before(pList, pNode, ele);
void insert_after(pList, pNode, ele);
void insert_at(pList, int, ele);

void remove_head(pList);
void remove_tail(pList);
void remove_node(pList, pNode);
void remove_at(pList, int);
void remove_val(pList, ele);
void remove_k(pList, ele, int);

pNode cycle_next(pList, pNode);
pNode cycle_prev(pList, pNode);

void print_list(pList);
int is_empty(pList);
int size(pList);
pList copy(pList);
void reverse(pList);
void clear(pList);
void concat(pList, pList);
pList split(pList, int);
void free_list(pList);

#ifdef QUEUE
typedef List Queue, *pQueue;
pQueue new_queue();
void enqueue(pQueue, ele);
ele dequeue(pQueue);
ele front(pQueue);
#endif

#ifdef STACK
typedef List Stack, *pStack;
pStack new_stack();
void push(pStack, ele);
ele pop(pStack);
ele top(pStack);
#endif

char *num[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {

#ifdef STACK
    /* Stack Test */
    printf("Stack Test\n");
    pStack stack = new_stack();
    for (int i = 0; i < 10; i++) {
        push(stack, num[i]);
    }
    print_list(stack);
    for (int i = 0; i < 10; i++) {
        printf("%s ", pop(stack));
    }
    printf("\n\n");
    free_list(stack);
#endif

#ifdef QUEUE
    /* Queue Test */
    printf("Queue Test\n");
    pQueue queue = new_queue();
    for (int i = 0; i < 10; i++) {
        enqueue(queue, num[i]);
    }
    print_list(queue);
    for (int i = 0; i < 10; i++) {
        printf("%s ", dequeue(queue));
    }
    printf("\n\n");
#endif
    /* List Test */
    printf("List Test\n");
    pList list = new_list_from_array(num, 10);
    /*
        num here is an one-dimensional array.
        if you use char num_two[10][10] = {"zero", "one", ...} here,
        the func cannot infer the size of the elements in the array.
        Because the size of the elements is expected to be sizeof(ele) = sizeof(char*).
    */
    print_list(list);

    remove_at(list, 3);
    print_list(list);

    insert_head(list, "HEAD");
    insert_after(list, find(list, "five"), "{AFTER five}");
    insert_before(list, find_at(list, 2), "{BEFORE loc 2}");
    insert_tail(list, "TAIL");
    insert_tail(list, "five");
    insert_tail(list, "five");
    insert_tail(list, "five");
    print_list(list);

    remove_val(list, "five");
    print_list(list);

    pList list2 = split(list, 5);
    print_list(list);
    print_list(list2);

    concat(list, list2);
    print_list(list);

    reverse(list);
    print_list(list);

    clear(list);

    return 0;
}

/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */
/* --------------------------------------------------------------- */

// create a node, return the pointer to the node
// not used by user
pNode new_node(ele val) {
    pNode node = (pNode)malloc(sizeof(Node));
    copy_ele(&node->val, val);
    node->next = node->prev = NULL;
    return node;
}

// create a list, return the pointer to the list
pList new_list() {
    pList list = (pList)malloc(sizeof(List));
    list->head = list->tail = NULL;
    list->size = 0;
    return list;
}

// create a list from an array, return the pointer to the list
// the length of the array is "len"
// Note: the array should be a one-dimensional array
pList new_list_from_array(ele *arr, int len) {
    pList list = new_list();
    for (int i = 0; i < len; i++) {
        insert_tail(list, arr[i]);
    }
    return list;
}

// get the head of the list
pNode get_head(pList list) {
    return list->head;
}

// get the tail of the list
pNode get_tail(pList list) {
    return list->tail;
}

// find the k-th node with the value "val"
pNode find_k(pList list, ele val, int k) {
    int cnt = 0;
    list_for_each(list, node) {
        if (equal_ele(node->val, val) == 0) {
            cnt++;
            if (cnt == k) {
                return node;
            }
        }
    }
    return NULL;
}

// find the first node with the value "val" using the function "equal_user"
// the function "equal_user" should return 0 if the two values are equal
pNode find_eq(pList list, ele val, int (*equal_user)(ele, ele)) {
    list_for_each(list, node) {
        if (equal_user(node->val, val) == 0) {
            return node;
        }
    }
    return NULL;
}

// find the first node with the value "val"
pNode find(pList list, ele val) {
    return find_eq(list, val, equal_ele);
}

// find the node at the index "index"
pNode find_at(pList list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Error: index out of range\n");
        return NULL;
    }
    pNode node;
    if (index < list->size / 2) {
        node = list->head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
    } else {
        pNode node = list->tail;
        for (int i = list->size - 1; i > index; i--) {
            node = node->prev;
        }
    }
    return node;
}

// count the number of nodes with the value "val"6
int count(pList list, ele val) {
    int cnt = 0;
    list_for_each(list, node) {
        if (equal_ele(node->val, val) == 0) {
            cnt++;
        }
    }
    return cnt;
}

// insert a node with the value "val" to the tail of the list
void insert_tail(pList list, ele val) {
    pNode node = new_node(val);
    if (list->size == 0) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}

// insert a node with the value "val" to the head of the list
void insert_head(pList list, ele val) {
    pNode node = new_node(val);
    if (list->size == 0) {
        list->head = list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }
    list->size++;
}

// insert a node with the value "val" before the node "node"
void insert_before(pList list, pNode node, ele val) {
    if (node == list->head) {
        insert_head(list, val);
    } else {
        pNode newNode = new_node(val);
        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;
        list->size++;
    }
}

// insert a node with the value "val" after the node "node"
void insert_after(pList list, pNode node, ele val) {
    if (node == list->tail) {
        insert_tail(list, val);
    } else {
        pNode newNode = new_node(val);
        newNode->next = node->next;
        newNode->prev = node;
        node->next->prev = newNode;
        node->next = newNode;
        list->size++;
    }
}

// insert a node with the value "val" at the position "pos"
void insert_at(pList list, int pos, ele val) {
    if (pos < 0 || pos > list->size) {
        printf("Error: insert position out of range\n");
        return;
    }
    if (pos == list->size) {
        insert_tail(list, val);
    } else {
        pNode node = find_at(list, pos);
        insert_before(list, node, val);
    }
}

// remove the head node
void remove_head(pList list) {
    if (list->size == 0) {
        printf("Error: list is empty\n");
        return;
    }
    pNode node = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }
    free(node);
    list->size--;
}

// remove the tail node
void remove_tail(pList list) {
    if (list->size == 0) {
        printf("Error: list is empty\n");
        return;
    }
    pNode node = list->tail;
    list->tail = list->tail->prev;
    if (list->tail == NULL) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }
    free(node);
    list->size--;
}

// remove the node "node"
void remove_node(pList list, pNode node) {
    if (list->size == 0) {
        printf("Error: list is empty\n");
        return;
    }
    if (node == list->head) {
        remove_head(list);
    } else if (node == list->tail) {
        remove_tail(list);
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
        list->size--;
    }
}

// remove the node at the position "pos"
void remove_at(pList list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Error: remove position out of range\n");
        return;
    }
    pNode node = find_at(list, pos);
    remove_node(list, node);
}

// remove all nodes with the value "val"
void remove_val(pList list, ele val) {
    list_for_each_safe(list, node, next) {
        if (equal_ele(node->val, val) == 0) {
            remove_node(list, node);
        }
    }
}

// remove k-th node with the value "val"
void remove_k(pList list, ele val, int k) {
    int cnt = 0;
    list_for_each_safe(list, node, next) {
        if (equal_ele(node->val, val) == 0) {
            cnt++;
            if (cnt == k) {
                remove_node(list, node);
                return;
            }
        }
    }
}

// next node if the list is a cycle list
// if the node is NULL, return the head node
pNode cycle_next(pList list, pNode node) {
    if (node == NULL) {
        return list->head;
    }
    return node->next == NULL ? list->head : node->next;
}

// previous node if the list is a cycle list
// if the node is NULL, return the tail node
pNode cycle_prev(pList list, pNode node) {
    if (node == NULL) {
        return list->tail;
    }
    return node->prev == NULL ? list->tail : node->prev;
}

// print the list
void print_list(pList list) {
    list_for_each(list, node) {
        print_ele(node->val);
    }
    printf("\n");
}

// return 1 if the list is empty, otherwise return 0
int is_empty(pList list) {
    return list->size == 0;
}

// return the size of the list
int size(pList list) {
    return list->size;
}

// copy the list
pList copy(pList list) {
    pList newList = new_list();
    list_for_each(list, node) {
        insert_tail(newList, node->val);
    }
    return newList;
}

// reverse the list
void reverse(pList list) {
    pNode node = list->head;
    list->head = list->tail;
    list->tail = node;
    while (node != NULL) {
        pNode next = node->next;
        node->next = node->prev;
        node->prev = next;
        node = next;
    }
}

// clear the list
// free all nodes and set the list to empty
void clear(pList list) {
    pNode node = list->head;
    while (node != NULL) {
        pNode next = node->next;
        free(node);
        node = next;
    }
    list->head = list->tail = NULL;
    list->size = 0;
}

// concat list2 to the tail of list1
// list2 will be empty after concat
void concat(pList list1, pList list2) {
    if (list1->size == 0) {
        list1->head = list2->head;
        list1->tail = list2->tail;
    } else if (list2->size != 0) {
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }
    list1->size += list2->size;
    list2->head = list2->tail = NULL;
    list2->size = 0;
}

// split the list at the position "pos"
// return the list after the position "pos"
// the list before the position "pos" will be the original list
pList split(pList list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Error: split position out of range\n");
        return NULL;
    }
    pList newList = new_list();
    if (pos == 0) {
        newList->head = list->head;
        newList->tail = list->tail;
        newList->size = list->size;
        list->head = list->tail = NULL;
        list->size = 0;
    } else if (pos == list->size - 1) {
        newList->head = list->tail;
        newList->tail = list->tail;
        newList->size = 1;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->size--;
    } else {
        pNode node = find_at(list, pos);
        newList->head = node->next;
        newList->tail = list->tail;
        newList->size = list->size - pos;
        list->tail = node;
        list->tail->next = NULL;
        list->size = pos;
    }
    return newList;
}

// free the list
// free all nodes and the list itself
void free_list(pList list) {
    clear(list);
    free(list);
}

#ifdef QUEUE
pQueue new_queue() {
    return new_list();
}
ele front(pQueue queue) {
    if (queue->size == 0) {
        printf("Error: queue is empty\n");
        return 0;
    }
    return queue->head->val;
}
void enqueue(pQueue queue, ele val) {
    insert_tail(queue, val);
}
ele dequeue(pQueue queue) {
    ele val = front(queue);
    remove_head(queue);
    return val;
}
#endif

#ifdef STACK
pStack new_stack() {
    return new_list();
}
ele top(pStack stack) {
    if (stack->size == 0) {
        printf("Error: stack is empty\n");
        return 0;
    }
    return stack->tail->val;
}
void push(pStack stack, ele val) {
    insert_tail(stack, val);
}
ele pop(pStack stack) {
    ele val = top(stack);
    remove_tail(stack);
    return val;
}
#endif