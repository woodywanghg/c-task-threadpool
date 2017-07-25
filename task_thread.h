/*
 * Copyright (C) feinno.com wanghonggang 2010-5-13
 */

#ifndef _TASK_THREAD_H_
#define _TASK_THREAD_H_

#include "assert.h"
#include "queue.h"
#include <pthread.h>
#include "task.h"
#include <linux/types.h>


struct task_thread_t
{
	int pause;
	pthread_t tid;
    pthread_mutex_t lock;
	struct queue_t* queue;	
	__u64   passed_tasks;
};

struct task_thread_t* create_task_thread();
void destroy_task_thread(struct task_thread_t* task_thread);
int enqueue_task_t(struct task_thread_t* task_thread, struct task_t* task);
void pause_thread(struct task_thread_t* task_thread);
void resume_thread(struct task_thread_t* task_thread);
inline int get_task_size(struct task_thread_t* task_thread);
inline __u64 get_passed_tasks(struct task_thread_t* task_thread);
void remove_task_id(struct task_thread_t* task_thread, int task_id);
void remove_task_all(struct task_thread_t* task_thread);

#endif /*_TASK_THREAD_H_*/
