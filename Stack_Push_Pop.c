// stack_ops.c

#include <stdio.h>
#include <stdlib.h>
#include "stack_ops.h"

// Top pointer and counter
struct Node* top = NULL;
int count = 0;

// Push operation
void push(int value) 
{
    if (count == STACKSIZE) 
    {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    count++;
    printf("Pushed %d\n", value);
}

// Pop operation
int pop(void) 
{
    if (top == NULL) 
    {
        printf("Stack Underflow!\n");
        return -1;
    }
    struct Node* temp = top;
    int popped = temp->data;
    top = top->next;
    free(temp);
    count--;
    return popped;
}

// Display stack
void display(void) 
{
    struct Node* current = top;
    printf("Stack (top -> bottom): ");
    while (current != NULL) 
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Wrapper for stack operations
int stack_push_pop_wrapper(int mode, int value) 
{
    if (mode == STACK_PUSH_MODE) 
    { // push
        push(value);
        return value;
    } 
    else if (STACK_POP_MODE == mode) 
    { //pop
        return pop();
    } 
    else 
    {
        printf("Invalid mode!\n");
        return -2;
    }
}
