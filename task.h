/*
 * Copyright (C) wanghonggang 2010-5-13
 */

#ifndef _TASK_H_
#define _TASK_H_

#include <stdio.h>

typedef void (*FUN0_T)();
typedef void (*FUN1_T)(void*);
typedef void (*FUN2_T)(void*, void*);
typedef void (*FUN3_T)(void*, void*, void*);
typedef void (*FUN4_T)(void*, void*, void*, void*);
typedef void (*FUN5_T)(void*, void*, void*, void*, void*);
typedef void (*FUN6_T)(void*, void*, void*, void*, void*, void*);

enum fun_type
{
	FUN_0 = 0,
	FUN_1 = 1,
	FUN_2 = 2,
	FUN_3 = 3,
	FUN_4 = 4,
	FUN_5 = 5,
	FUN_6 = 6,
	FUN_7 = 7,
	FUN_8 = 8,
	FUN_9 = 9
};

enum
{
	TASK_KEEP   = 0,
	TASK_REMOVE = 1
};

struct task_t
{
	union 
	{
		struct
		{
			FUN0_T fun_ptr;
		} fun0;

		struct	
		{
			void* p1;
			FUN1_T fun_ptr;
		} fun1;

		struct	
		{
			void* p1;
			void* p2;
			FUN2_T fun_ptr;
		} fun2;

		struct	
		{
			void* p1;
			void* p2;
			void* p3;
			FUN3_T fun_ptr;
		} fun3;

		struct	
		{
			void* p1;
			void* p2;
			void* p3;
			void* p4;
			FUN4_T fun_ptr;
		} fun4;

		struct	
		{
			void* p1;
			void* p2;
			void* p3;
			void* p4;
			void* p5;
			FUN5_T fun_ptr;
		} fun5;

		struct	
		{
			void* p1;
			void* p2;
			void* p3;
			void* p4;
			void* p5;
			void* p6;
			FUN6_T fun_ptr;
		} fun6;
	}fun;
	
	/*@ 1:remove, 0:don't remove */ 
	int id;
	int remove;
	enum fun_type type;
};

struct task_t* create_task(enum fun_type type, int remove, int id);

#endif /* _TASK_H_ */
