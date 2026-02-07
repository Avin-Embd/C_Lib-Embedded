// stack_ops.h

#ifndef STACK_OPS_H
#define STACK_OPS_H

#define STACKSIZE 5

// Macro definitions for operation modes
#define STACK_PUSH_MODE 0
#define STACK_POP_MODE 1

struct Node 
{
    int data;
    struct Node* next;
};

void push(int value);
int pop(void);
void display(void);
int stack_push_pop_wrapper(int mode, int value);

#endif // STACK_OPS_H
