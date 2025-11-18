#ifndef ULT_CAPTURE_PUB_H
#define ULT_CAPTURE_PUB_H

#include "fork_pub.h"
#include "redirect_pub.h"
#include "status_pub.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum e_capture_mode
{
	GET_RET,
	GET_OUT,
	GET_ERR,
	GET_BOTH,
	GET_RET_OUT,
	GET_RET_ERR,
	GET_RET_BOTH,
}	t_capture_mode;

static const t_redirect_mode g_capture_to_redirect[] = {
	[GET_RET]		= -1,
    [GET_OUT]       = R_STDOUT,
    [GET_ERR]       = R_STDERR,
    [GET_BOTH]      = R_BOTH,
    [GET_RET_OUT]   = R_STDOUT,
    [GET_RET_ERR]   = R_STDERR,
    [GET_RET_BOTH]  = R_BOTH
};

typedef struct s_capture {
	t_status	status;
	intptr_t	ret;
	char		*out;
} t_capture;

typedef struct s_capture_res
{
	intptr_t	ret;
	char		*out;
}	t_capture_res;

void	_fut_capture_parent(t_context *ctx, t_capture *capture);
void	_fut_capture_child(t_context *ctx, t_capture_res *res);

#define capture(mode, timeout, expr, capture_pointer)			\
	do {														\
		t_context	ctx;										\
																\
		*capture_pointer = {0};									\
		capture_pointer->status.timeout = timeout				\
		_fut_fork_init(&ctx, timeout);							\
		if (ctx.child_pid > 0)									\
			_fut_capture_parent(&ctx, capture_pointer);			\
		else													\
		{														\
			t_capture_res capture_res = {0};					\
			if (mode != GET_RET)								\
				redirect_start(g_capture_to_redirect[mode]);	\
			capture_res.ret = (intptr_t)expr;					\
			if (mode != GET_RET)								\
			{													\
				capture_res.out = redirect_read();				\
				redirect_stop();								\
			}													\
			_fut_capture_child(&ctx, &capture_res);				\
		}														\
	} while (0)

#endif
