#include "task.h"
#include <stdlib.h>

struct task_t* create_task(enum fun_type type, int remove, int id)
{
	struct task_t* task = calloc(1, sizeof(struct task_t));
	if(NULL == task)
	{
		return NULL;
	}
	
	task->id     = id;
	task->type   = type;
	task->remove = remove;
	
	return task;
}

