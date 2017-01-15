#include "queue_private.h"
#include <stdlib.h>
#include <upo/error.h>

upo_queue_t upo_queue_create()
{
    upo_queue_t queue = malloc(sizeof(struct upo_queue_s));
    if (queue == NULL)
    {
        fprintf(stderr, "Unable to create a queue!\n");
        abort();
    }
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;

    return queue;
}

void upo_queue_destroy(upo_queue_t queue, int destroy_data)
{
    if (queue != NULL)
    {
        upo_queue_clear(queue, destroy_data);
        free(queue);
    }
}

void upo_queue_clear(upo_queue_t queue, int destroy_data)
{
    if (queue != NULL)
    {
        while(queue->front != NULL)
        {
            upo_queue_dequeue(queue, destroy_data);
        }
    }
}

void upo_queue_enqueue(upo_queue_t queue, void *data)
{
    upo_queue_node_t* newNode;
    if (queue != NULL)
    {
        newNode = malloc(sizeof(struct upo_queue_node_s));
        if (newNode == NULL)
        {
            fprintf(stderr, "Unable to create a new node!\n");
            abort();
        }
        newNode->data = data;
        newNode->prev = NULL;
        if (queue->front == NULL)
        {
            newNode->next = NULL;
            queue->front = newNode;
            queue->back = newNode;
        }
        else
        {
            queue->back->prev = newNode;
            newNode->next = queue->back;
            queue->back = newNode;
        }
        queue->size += 1;
    }
}

void upo_queue_dequeue(upo_queue_t queue, int destroy_data)
{
    if (queue != NULL && queue->front != NULL)
    {
        upo_queue_node_t* node = queue->front;
        queue->front = queue->front->prev;
        if (queue->front != NULL)
            queue->front->next = NULL;
        if (destroy_data)
            free(node->data);
        free(node);
        queue->size -= 1;
    }
}

void* upo_queue_peek(const upo_queue_t queue)
{
    if (upo_queue_is_empty(queue))
        return NULL;
    return queue->front->data;
}

size_t upo_queue_size(const upo_queue_t queue)
{
    if (queue != NULL)
        return queue->size;
    return 0;
}

int upo_queue_is_empty(const upo_queue_t queue)
{
    if (queue != NULL)
        return queue->size == 0 ? 1 : 0;
    return 1;
}
