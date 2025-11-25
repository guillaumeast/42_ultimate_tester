#ifndef ULT_MEMCHECK_PUB_H
#define ULT_MEMCHECK_PUB_H

#include <stddef.h>

typedef enum e_mem_mode
{
	LEAKS,
	SAFETY,
}	t_mem_mode;

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr);
void	_memcheck_enable(t_mem_mode mode);
void	_memcheck_child(const char *expr);

#define memleaks(timeout, expr)				\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(LEAKS);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#define memsafety(timeout, expr)			\
	do {									\
		_fork_init(timeout);				\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expr);		\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(SAFETY);		\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#endif
