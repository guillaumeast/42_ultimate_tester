#ifndef ULT_MEMCHECK_PUB_H
#define ULT_MEMCHECK_PUB_H

#include <stddef.h>

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr);
void	_memcheck_enable(void);
void	_memcheck_child(const char *expr);

#define memcheck(timeout, expr)				\
	do {									\
		_fork_init(timeout);				\
		if (ctx.child_pid > 0)				\
			_memcheck_parent(#expr);		\
		if (ctx.child_pid == 0)				\
		{									\
			_memcheck_enable();				\
			expr;							\
			_memcheck_child(#expr);			\
		}									\
	} while (0)

#endif
