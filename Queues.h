#ifndef QUEUE_OPS_H
#define QUEUE_OPS_H

#include <stdint.h>

#define QUEUE_SIZE 10U

// Return status macros
#define Q_RET_STATUS_SUCCESS 0U
#define Q_RET_STATUS_FAIL 1U
#define Q_INVALID_STATUS 2U

typedef uint8_t RET_Q_STATUS;

typedef struct 
{
    uint32_t write_idx;
    uint32_t read_idx;
    uint32_t idx_pos;
    uint8_t data_buff[QUEUE_SIZE];
} queue_type;

// Queue function prototypes
RET_Q_STATUS queue_empty(queue_type *queue_handler);
RET_Q_STATUS queue_full(queue_type *queue_handler);
RET_Q_STATUS enqueue(queue_type *queue_handler, char ch);
RET_Q_STATUS dequeue(queue_type *queue_handler, char *ch);
RET_Q_STATUS queue_print(queue_type *queue_handler);

// Wrapper operation mode macros
#define QUEUE_ENQUEUE_MODE 0
#define QUEUE_DEQUEUE_MODE 1

// Wrapper function prototype
RET_Q_STATUS queue_op_wrapper(queue_type *queue_handler, int mode, char *ch);

#endif // QUEUE_OPS_H
