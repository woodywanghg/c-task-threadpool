/*
 * Copyright (C) wanghonggang 2010-5-13
 */

#ifndef _TASK_THREAD_POOL_H_
#define _TASK_THREAD_POOL_H_

#include "task.h"
#include <linux/types.h>

struct task_thread_pool_t
{
	int  size;
	int  sched_thread_id;
	struct task_thread_t** threads;
};

struct task_thread_pool_t* init_task_thread_pool(int size);
int destroy_task_thread_pool(struct task_thread_pool_t* task_thread_pool); 
int enqueue_task(struct task_thread_pool_t* task_thread_pool, struct task_t* task);
int enqueue_task_index(struct task_thread_pool_t* task_thread_pool, struct task_t* task, int index);
int pause_task_thread_pool(struct task_thread_pool_t* task_thread_pool);
int resume_task_thread_pool(struct task_thread_pool_t* task_thread_pool);
int get_pool_task_size(struct task_thread_pool_t* task_thread_pool);
__u64 get_pool_passed_tasks(struct task_thread_pool_t* task_thread_pool);
void pool_remove_task_id(struct task_thread_pool_t* task_thread_pool, int task_id);
void pool_remove_task_id_index(struct task_thread_pool_t* task_thread_pool, int task_id, int index);
void pool_remove_task_all(struct task_thread_pool_t* task_thread_pool);
#endif /* _TASK_THREAD_POOL_H_ */
