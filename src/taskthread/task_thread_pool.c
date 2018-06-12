#include "task_thread_pool.h"
#include "task_thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct task_thread_pool_t* init_task_thread_pool(int size)
{
	assert(size > 0);
	struct task_thread_pool_t* task_thread_pool = calloc(1, sizeof(struct task_thread_pool_t));
	if(NULL == task_thread_pool)
	{
		return NULL;
	}
	
	task_thread_pool->size = size;	
	task_thread_pool->sched_thread_id = 0;

	task_thread_pool->threads = calloc(size, sizeof(struct task_thread_t*));
	int i = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		struct task_thread_t* task_thread = create_task_thread();
		if(NULL == task_thread)
		{
			break;
		}
		task_thread_pool->threads[i] = task_thread;
	}
	
	if(i != task_thread_pool->size)
	{
		int j = 0;
		for(j = 0; j < i; j++)
		{
			free(task_thread_pool->threads[j]);
		}
		
		free(task_thread_pool->threads);
		free(task_thread_pool);

		return NULL;
	}
	
	return task_thread_pool;
}

int destroy_task_thread_pool(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		destroy_task_thread(task_thread_pool->threads[i]);
	}

	return 0;
}

int enqueue_task(struct task_thread_pool_t* task_thread_pool, struct task_t* task)
{
	int thread_index = task_thread_pool->sched_thread_id++ % task_thread_pool->size;	
	return enqueue_task_t(task_thread_pool->threads[thread_index], task);	
}

int enqueue_task_index(struct task_thread_pool_t* task_thread_pool, struct task_t* task, int index)
{
	if(index >= task_thread_pool->size)
	{
		return -1;
	}

	return enqueue_task_t(task_thread_pool->threads[index], task);	
}

int pause_task_thread_pool(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		pause_thread(task_thread_pool->threads[i]);
	}

	return 0;
}

int resume_task_thread_pool(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
    for(i = 0; i < task_thread_pool->size; i++)
    {
        resume_thread(task_thread_pool->threads[i]);
    }

    return 0;
}

int get_pool_task_size(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
	int size = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		size += get_task_size(task_thread_pool->threads[i]);
	} 
	
	return size;
}

int get_pool_passed_tasks(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
	int size = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
			size += get_passed_tasks(task_thread_pool->threads[i]);
	}

	return size;
}

void pool_remove_task_id(struct task_thread_pool_t* task_thread_pool, int task_id)
{
	int i = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		remove_task_id(task_thread_pool->threads[i], task_id);
	} 
}

void pool_remove_task_id_index(struct task_thread_pool_t* task_thread_pool, int task_id, int index)
{
	remove_task_id(task_thread_pool->threads[index], task_id);
}

void pool_remove_task_all(struct task_thread_pool_t* task_thread_pool)
{
	int i = 0;
	for(i = 0; i < task_thread_pool->size; i++)
	{
		remove_task_all(task_thread_pool->threads[i]);
	} 
}
