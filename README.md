## What is c-task-threadpool?

>The c-task-threadpool library looks like C++ thread bind functor model
>
>The c language function can package into task struct, the task is enqueued into the list that thread runable

## Mechanism
![Mechanism](https://github.com/woodywanghg/gitpicture/blob/master/threadpool_ss.png)

## APIs
* 1. struct task_thread_pool_t* init_task_thread_pool(int size) *size: thread number*
* 2. int enqueue_task(struct task_thread_pool_t* task_thread_pool, struct task_t* task); *Enqueue the task into thread (Rotation model)*
* 3. int enqueue_task_index(struct task_thread_pool_t* task_thread_pool, struct task_t* task, int index); *Enqueue the task into thread (index model)*
* 4. Remove task
     *  void pool_remove_task_id(struct task_thread_pool_t* task_thread_pool, int task_id);
	 *  void pool_remove_task_id_index(struct task_thread_pool_t* task_thread_pool, int task_id, int index);
	 *  void pool_remove_task_all(struct task_thread_pool_t* task_thread_pool);
* 5. Pause & resume task
     *  int pause_task_thread_pool(struct task_thread_pool_t* task_thread_pool);
     *  int resume_task_thread_pool(struct task_thread_pool_t* task_thread_pool);

* 6. int get_pool_task_size(struct task_thread_pool_t* task_thread_pool); *Get thread number*
* 7. int get_pool_passed_tasks(struct task_thread_pool_t* task_thread_pool); *Get tasks number*

## How to build & install?
```{r, engine='bash', build}

Step 0.  c-task-threadpool dir

Step 1.  cd build
Step 2.  cmake .
Step 3.  make
Step 4.  make install
```

