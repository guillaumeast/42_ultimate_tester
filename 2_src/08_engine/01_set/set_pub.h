#ifndef ULT_SET_PUB_H
#define ULT_SET_PUB_H

#include "result_pub.h"
#include <stddef.h>

typedef void (*t_test_fn)(void);

typedef struct s_set
{
	const char		*name;
	size_t			timeout;
	t_test_fn		func;
	t_result		result;
	struct s_set	*next;
}	t_set;

void	set_register(t_set *set);

#define Test(name, timeout) 									\
	static void name(void); 									\
	static t_set _set_##name =									\
	{															\
		#name,													\
		timeout,												\
		name,													\
		{ {QUEUED, 0, 0, 0}, 0, 0, 0, 0, 0, 0 },				\
		NULL													\
	};															\
	__attribute__((constructor(101)))							\
	static void _register_##name(void)							\
	{															\
		set_register(&_set_##name);								\
	}															\
	static void name(void)

#endif
