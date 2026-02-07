#include <stdio.h>
#include <stdlib.h>
#include "linked_list_ops.h"

// Insert at the beginning
struct Node* insert_at_beginning(struct Node* head, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = head;
    return new_node;  // New head
}

// Insert at the end
struct Node* insert_at_end(struct Node* head, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    if (head == NULL)
        return new_node;

    struct Node* last = head;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;

    return head;
}

// Insert after a given node
void insert_after(struct Node* prev_node, int new_data)
{
    if (prev_node == NULL)
    {
        printf("Previous node cannot be NULL\n");
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

// Delete a node by key
struct Node* delete_node(struct Node* head, int key)
{
    if (head == NULL)
        return head;

    if (head->data == key)
    {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node* current = head;
    while (current->next != NULL && current->next->data != key)
        current = current->next;

    if (current->next != NULL)
    {
        struct Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return head;
}

// Search for a node
int search_node(struct Node* head, int key)
{
    struct Node* current = head;
    while (current != NULL)
    {
        if (current->data == key)
            return 1;
        current = current->next;
    }
    return 0;
}

// Sort linked list using simple bubble sort
void sort_linked_list(struct Node* head)
{
    if (head == NULL)
        return;

    struct Node *current, *index;
    int temp;
    for (current = head; current != NULL; current = current->next)
    {
        for (index = current->next; index != NULL; index = index->next)
        {
            if (current->data > index->data)
            {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}

// Print linked list
void print_list(struct Node* node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Wrapper function performing linked list operations
// mode - indicates operation, param - data or key, extra_node - for insert_after
// Returns 1 for success or found in search, 0 otherwise; updates head_ref if needed
int linked_list_op_wrapper(struct Node** head_ref, int mode, int param, struct Node* extra_node)
{
    switch (mode)
    {
        case LIST_OP_INSERT_BEGIN:
            *head_ref = insert_at_beginning(*head_ref, param);
            return 1;
        case LIST_OP_INSERT_END:
            *head_ref = insert_at_end(*head_ref, param);
            return 1;
        case LIST_OP_INSERT_AFTER:
            insert_after(extra_node, param);
            return 1;
        case LIST_OP_DELETE:
            *head_ref = delete_node(*head_ref, param);
            return 1;
        case LIST_OP_SEARCH:
            return search_node(*head_ref, param);
        case LIST_OP_SORT:
            sort_linked_list(*head_ref);
            return 1;
        case LIST_OP_PRINT:
            print_list(*head_ref);
            return 1;
        default:
            printf("Invalid operation mode\n");
            return 0;
    }
}
