#ifndef UPO_QUEUE_PRIVATE_H
#define UPO_QUEUE_PRIVATE_H

#include <stddef.h>
#include <upo/queue.h>

struct upo_queue_node_s {
    void* data;
    struct upo_queue_node_s* next;
    struct upo_queue_node_s* prev;
};

typedef struct upo_queue_node_s upo_queue_node_t;

struct upo_queue_s {
    upo_queue_node_t* front;
    upo_queue_node_t* back;
    size_t size;
};

#endif /* UPO_QUEUE_PRIVATE_H */
