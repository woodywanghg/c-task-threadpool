#include "task_thread.h"
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include "task.h"

static void* run(void* para);
static inline void task_proxy(struct task_t* task);

struct task_thread_t* create_task_thread()
{
	struct task_thread_t* task_thread = calloc(1, sizeof(struct task_thread_t));	
	if(NULL == task_thread)
	{
		return NULL;
	}	
	
	task_thread->pause = 0;
	pthread_mutex_init(&task_thread->lock, NULL);
	task_thread->queue = init_queue();
	
    if(pthread_create(&task_thread->tid, NULL, run, (void*)task_thread))
    {
        return NULL;
    }

    return task_thread;	
}

void destroy_task_thread(struct task_thread_t* task_thread)
{
	pthread_cancel(task_thread->tid);
	pthread_join(task_thread->tid, NULL);
	
	int queue_size = queue_get_size(task_thread->queue);
	while(queue_size > 0)
	{
		queue_node_t *note_t = queue_get_first(task_thread->queue);
		if (note_t != NULL)
		{
			struct task_t* task = (struct task_t*)note_t->ptr;
			queue_remove(task_thread->queue, task);
			free(task);
		}

		queue_size--;	
	}
	
	destroy_queue(task_thread->queue);
}

void* run(void* para)
{
	struct task_thread_t* task_thread= (struct task_thread_t*)para;
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    int queue_size = 0;
	struct timeval tv;

	while(1)
	{
    	pthread_mutex_lock(&task_thread->lock);
		queue_size = queue_get_size(task_thread->queue);
		while(queue_size > 0 && !task_thread->pause)
		{
			queue_node_t *node = queue_get_first(task_thread->queue);
			if(node != NULL)
			{
				struct task_t* task = (struct task_t*)node->ptr;
				if(task->remove)
				{
					queue_remove(task_thread->queue, task);
				}
				
				task_thread->passed_tasks++;
				pthread_mutex_unlock(&task_thread->lock);
				task_proxy(task);
				if(task->remove)
				{
					free(task);
				}
			}

			pthread_testcancel();
			pthread_mutex_lock(&task_thread->lock);
                	queue_size = queue_get_size(task_thread->queue);
		}

		pthread_mutex_unlock(&task_thread->lock);

		tv.tv_sec = 0;
		tv.tv_usec = 10;
		select(0, NULL, NULL, NULL, &tv);
	}
	
	return 0;
} 

inline void task_proxy(struct task_t* task)
{
	switch(task->type)
	{
	case FUN_0:
		task->fun.fun0.fun_ptr();
		break;
	case FUN_1:
		task->fun.fun1.fun_ptr(task->fun.fun1.p1);
		break;
	case FUN_2:
		task->fun.fun2.fun_ptr(task->fun.fun2.p1, task->fun.fun2.p2);
		break;
	case FUN_3:
		task->fun.fun3.fun_ptr(task->fun.fun3.p1, task->fun.fun3.p2, task->fun.fun3.p3);
		break;
	case FUN_4:
		task->fun.fun4.fun_ptr(task->fun.fun4.p1, task->fun.fun4.p2, task->fun.fun4.p3, task->fun.fun4.p4);
		break;
	case FUN_5:
		task->fun.fun5.fun_ptr(task->fun.fun5.p1, task->fun.fun5.p2, task->fun.fun5.p3, task->fun.fun5.p4, task->fun.fun5.p5);
		break;
	case FUN_6:
		task->fun.fun6.fun_ptr(task->fun.fun6.p1, task->fun.fun6.p2, task->fun.fun6.p3, task->fun.fun6.p4, task->fun.fun6.p5, task->fun.fun6.p6);
		break;
	default:
		break;
	}
}

int enqueue_task_t(struct task_thread_t* task_thread, struct task_t* task)
{
	int ret = 0;
	pthread_mutex_lock(&task_thread->lock);
	if(NULL == queue_add(task_thread->queue, task, sizeof(struct task_t)))
	{
		ret = -1;
	}
	pthread_mutex_unlock(&task_thread->lock);

	
	return ret;
}

void pause_thread(struct task_thread_t* task_thread)
{
	pthread_mutex_lock(&task_thread->lock);
	task_thread->pause = 1;
	pthread_mutex_unlock(&task_thread->lock);	
}

void resume_thread(struct task_thread_t* task_thread)
{
	pthread_mutex_lock(&task_thread->lock);
	task_thread->pause = 0;
	pthread_mutex_unlock(&task_thread->lock);	
}

int get_task_size(struct task_thread_t* task_thread)
{
	pthread_mutex_lock(&task_thread->lock);
	int size = queue_get_size(task_thread->queue);	
    pthread_mutex_unlock(&task_thread->lock);
	
	return size;
}

__u64 get_passed_tasks(struct task_thread_t* task_thread)
{
	pthread_mutex_lock(&task_thread->lock);
        __u64 size = task_thread->passed_tasks;
	pthread_mutex_unlock(&task_thread->lock);
	return size;
}

void remove_task_id(struct task_thread_t* task_thread, int task_id)
{
	pthread_mutex_lock(&task_thread->lock);

	queue_node_t* node = queue_get_first(task_thread->queue);
	queue_node_t* next = NULL;
	if(node != NULL)
	{
		do
		{
			next = queue_get_next(node);
			if(node != NULL)
			{
				struct task_t* task = (struct task_t*)node->ptr;
				if(task->id == task_id)
				{
					queue_remove(task_thread->queue, task);
					free(task);
				}
			}

			node = next;
		}while(next!= NULL);
	}

    pthread_mutex_unlock(&task_thread->lock);
}

void remove_task_all(struct task_thread_t* task_thread)
{
	pthread_mutex_lock(&task_thread->lock);

	queue_node_t* node = queue_get_first(task_thread->queue);
	queue_node_t* next = NULL;
	if(node != NULL)
	{
		do
		{
			next = queue_get_next(node);
			if(node != NULL)
			{
				struct task_t* task = (struct task_t*)node->ptr;
				queue_remove(task_thread->queue, task);
				free(task);
			}

			node = next;
		}while(next!= NULL);
	}

    pthread_mutex_unlock(&task_thread->lock);
}
