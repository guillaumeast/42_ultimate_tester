#ifndef ULT_MEMCHECK_PUB_H
#define ULT_MEMCHECK_PUB_H

#include "fork_pub.h"

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr, t_context *ctx);
void	_memcheck_enable(void);
void	_memcheck_child(const char *expr, t_context *ctx);

#define memcheck(timeout, expr)				\
	do {									\
		t_context	ctx;					\
											\
		_fork_init(&ctx, timeout);			\
		if (ctx.child_pid > 0)				\
			_memcheck_parent(#expr, &ctx);	\
		if (ctx.child_pid == 0)				\
		{									\
			_memcheck_enable();				\
			expr;							\
			_memcheck_child(#expr, &ctx);	\
		}									\
	} while (0)

#endif
