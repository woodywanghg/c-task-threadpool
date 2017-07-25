#ifndef _QUEUE_H_
#define _QUEUE_H_
typedef enum {
	QUEUE_RESERVE_DATA = 0x01, //释放元素节点时候不释放数据指针
} queue_flag_t;

typedef struct queue_node_t {
	void *ptr;
	int size;
	struct queue_node_t *next;
} queue_node_t;

typedef struct queue_t {
	queue_node_t *head, *tail;
	int size;
	int flag_value;
} queue_t;

typedef int (*queue_find_key_t) (void *data, void *key);

#ifdef __cplusplus
extern "C" {
#endif
	queue_t *init_queue();
	void destroy_queue(queue_t * queue);
	void *queue_find_key(queue_t * queue, queue_find_key_t cb, void *key);
	queue_node_t *queue_add(queue_t * queue, void *data, int size);
	int queue_batch_add(queue_t * dest_queue, queue_t* src_queue);
	int queue_del(queue_t * queue, queue_node_t * data);
	int queue_remove(queue_t * queue, void *data);
	int queue_clear(queue_t * queue);
	queue_node_t *queue_get_first(queue_t * queue);
	queue_node_t *queue_get_next(queue_node_t * next);
	int queue_set_flag(queue_t* queue, queue_flag_t value);
	int queue_unset_flag(queue_t* queue, queue_flag_t value);
	int queue_get_size(queue_t* queue);
#ifdef __cplusplus
}
#endif
#endif
