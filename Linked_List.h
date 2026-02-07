#ifndef LINKED_LIST_OPS_H
#define LINKED_LIST_OPS_H

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Insert function prototypes
struct Node* insert_at_beginning(struct Node* head, int new_data);
struct Node* insert_at_end(struct Node* head, int new_data);
void insert_after(struct Node* prev_node, int new_data);

// Delete function prototype
struct Node* delete_node(struct Node* head, int key);

// Search function prototype
int search_node(struct Node* head, int key);

// Sort function prototype
void sort_linked_list(struct Node* head);

// Print function prototype
void print_list(struct Node* node);

// Wrapper operation mode macros
#define LIST_OP_INSERT_BEGIN 0
#define LIST_OP_INSERT_END 1
#define LIST_OP_INSERT_AFTER 2
#define LIST_OP_DELETE 3
#define LIST_OP_SEARCH 4
#define LIST_OP_SORT 5
#define LIST_OP_PRINT 6

// Wrapper function prototype
int linked_list_op_wrapper(struct Node** head_ref, int mode, int param, struct Node* extra_node);

#endif // LINKED_LIST_OPS_H
