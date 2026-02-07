#include <stdio.h>
#include "queue_ops.h"

RET_Q_STATUS queue_empty(queue_type *queue_handler)
{
    if (queue_handler == NULL) 
        return Q_INVALID_STATUS;
    return (queue_handler->idx_pos == 0) ? Q_RET_STATUS_SUCCESS : Q_INVALID_STATUS;
}

RET_Q_STATUS queue_full(queue_type *queue_handler)
{
    if (queue_handler == NULL) 
        return Q_INVALID_STATUS;
    return (queue_handler->idx_pos == QUEUE_SIZE) ? Q_RET_STATUS_SUCCESS : Q_INVALID_STATUS;
}

RET_Q_STATUS enqueue(queue_type *queue_handler, char ch)
{
    if (queue_handler == NULL) 
        return Q_INVALID_STATUS;

    if (queue_full(queue_handler) == Q_RET_STATUS_SUCCESS) 
        return Q_RET_STATUS_FAIL;

    queue_handler->data_buff[queue_handler->write_idx] = ch;
    queue_handler->idx_pos++;
    if (queue_handler->write_idx == QUEUE_SIZE - 1)
        queue_handler->write_idx = 0;
    else
        queue_handler->write_idx++;
    return Q_RET_STATUS_SUCCESS;
}

RET_Q_STATUS dequeue(queue_type *queue_handler, char *ch)
{
    if (queue_handler == NULL) 
        return Q_INVALID_STATUS;

    if (queue_empty(queue_handler) == Q_RET_STATUS_SUCCESS) 
        return Q_RET_STATUS_FAIL;

    *ch = queue_handler->data_buff[queue_handler->read_idx];
    queue_handler->idx_pos--;
    if (queue_handler->read_idx == QUEUE_SIZE - 1)
        queue_handler->read_idx = 0;
    else
        queue_handler->read_idx++;
    return Q_RET_STATUS_SUCCESS;
}

RET_Q_STATUS queue_print(queue_type *queue_handler)
{
    if (queue_handler == NULL) 
        return Q_INVALID_STATUS;
    
    printf("Queue content: ");
    uint32_t idx = queue_handler->read_idx;
    for (uint32_t i = 0; i < queue_handler->idx_pos; i++)
    {
        printf("%c ", queue_handler->data_buff[idx]);
        idx = (idx == QUEUE_SIZE - 1) ? 0 : idx + 1;
    }
    printf("\n");
    return Q_RET_STATUS_SUCCESS;
}

RET_Q_STATUS queue_op_wrapper(queue_type *queue_handler, int mode, char *ch)
{
    if (mode == QUEUE_ENQUEUE_MODE)
    {
        return enqueue(queue_handler, *ch);
    }
    else if (mode == QUEUE_DEQUEUE_MODE)
    {
        return dequeue(queue_handler, ch);
    }
    else
    {
        printf("Invalid mode!\n");
        return Q_INVALID_STATUS;
    }
}
