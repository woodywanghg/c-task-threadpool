#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
queue_t *init_queue() {
    queue_t *queue = calloc(1, sizeof(queue_t));
    return queue;
}

void destroy_queue(queue_t * queue) {
    queue_node_t *curnode = NULL;
    queue_node_t *prenode = NULL;
    assert(queue != NULL);
    curnode = queue->head;
    while (curnode != NULL) {
        if( (queue->flag_value & QUEUE_RESERVE_DATA) == QUEUE_RESERVE_DATA ) {
            if (curnode->ptr != NULL) {
                free(curnode->ptr);
            }
        }
        prenode = curnode;
        curnode = curnode->next;
        free(prenode);
    }
    free(queue);
}

void *queue_find_key(queue_t * queue, queue_find_key_t cb, void *key) {
    queue_node_t *curnode = NULL;
    assert(queue != NULL);
    if( cb == NULL ) {
        return NULL;
    }
    curnode = queue->head;
    while (curnode != NULL) {
        if (cb(curnode->ptr, key) == 0) {
            return curnode->ptr;
        }
        curnode = curnode->next;
    }
    return NULL;
}

queue_node_t *queue_add(queue_t * queue, void *data, int size) {
    queue_node_t *node = NULL;
    assert(queue != NULL);
    node = (queue_node_t *) calloc(1, sizeof(queue_node_t));
    node->ptr = data;
    node->size = size;
    node->next = NULL;
    if (queue->head != NULL) {
        queue->tail->next = node;
        queue->tail = node;
    } else {
        queue->head = node;
        queue->tail = node;
    }
    queue->size++;
    return node;
}

int queue_batch_add(queue_t * dest_queue, queue_t* src_queue) {
	return 0;
}

int queue_del(queue_t * queue, queue_node_t * node) {
    queue_node_t *curnode = NULL;
    queue_node_t *prenode = NULL;
    assert(queue != NULL);
    curnode = queue->head;
    while (curnode != NULL) {
        if (curnode == node) {
            if (curnode == queue->head) {
                queue->head = curnode->next;
            } else {
                prenode->next = curnode->next;
            }
            if (curnode == queue->tail) {
                queue->tail = prenode;
            }
            if( (queue->flag_value & QUEUE_RESERVE_DATA) == QUEUE_RESERVE_DATA ) {
                if( curnode->ptr ) {
                    free(curnode->ptr);
                }
            }
            free(curnode);
            queue->size--;
            if( queue->size < 0 ) {
            	queue->size = 0;
            }
            return 0;
        }
        prenode = curnode;
        curnode = curnode->next;
    }
    return -1;
}

int queue_remove(queue_t * queue, void *data) {
    queue_node_t *curnode = NULL;
    queue_node_t *prenode = NULL;
    assert(queue != NULL);
    curnode = queue->head;
    if (data == NULL) {
        return -1;
    }
    while (curnode != NULL) {
        if (curnode->ptr == data) {
            if (curnode == queue->head) {
                queue->head = curnode->next;
            } else {
                prenode->next = curnode->next;
            }
            if (curnode == queue->tail) {
                queue->tail = prenode;
            }
            if( (queue->flag_value & QUEUE_RESERVE_DATA) == QUEUE_RESERVE_DATA ) {
                if( curnode->ptr ) {
                    free(curnode->ptr);
                }
            }
            free(curnode);
            queue->size--;
            if( queue->size < 0 ) {
            	queue->size = 0;
            }
            return 0;
        }
        prenode = curnode;
        curnode = curnode->next;
    }
    return -1;
}

int queue_clear(queue_t * queue) {
    queue_node_t *curnode = NULL;
    queue_node_t *prenode = NULL;
    assert(queue != NULL);
    curnode = queue->head;
    while (curnode != NULL) {
        prenode = curnode;
        curnode = curnode->next;
        if( (queue->flag_value & QUEUE_RESERVE_DATA) == QUEUE_RESERVE_DATA ) {
            if( prenode->ptr ) {
                free(prenode->ptr);
            }
        }
        free(prenode);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return 0;
}

queue_node_t *queue_get_first(queue_t * queue) {
    assert(queue != NULL);
    return queue->head;
}

queue_node_t *queue_get_next(queue_node_t * node) {
    assert(node != NULL);
    return node->next;
}

int queue_set_flag(queue_t* queue, queue_flag_t value) {
    queue->flag_value |= value;
    return queue->flag_value;
}

int queue_unset_flag(queue_t* queue, queue_flag_t value) {
    queue->flag_value &= ~value;
    return queue->flag_value;
}

int queue_get_size(queue_t* queue) {
	if(queue == NULL ) {
		return 0;
	}
	return queue->size;
}
