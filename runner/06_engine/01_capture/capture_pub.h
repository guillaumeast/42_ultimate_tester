#ifndef ULT_CAPTURE_PUB_H
#define ULT_CAPTURE_PUB_H

#include "fork_pub.h"
#include "redirect_pub.h"
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

typedef struct s_capture {
	bool		ok;
	bool		crashed;
	bool		timed;
	int			signal;
	intptr_t	ret;
	char		*out;
} t_capture;

typedef struct s_capture_res
{
	intptr_t	ret;
	char		*out;
}	t_capture_res;

static const t_redirect_mode g_capture_to_redirect[] = {
	[GET_RET]		= -1,
    [GET_OUT]       = R_STDOUT,
    [GET_ERR]       = R_STDERR,
    [GET_BOTH]      = R_BOTH,
    [GET_RET_OUT]   = R_STDOUT,
    [GET_RET_ERR]   = R_STDERR,
    [GET_RET_BOTH]  = R_BOTH
};

#define capture(mode, expr, res_pointer)					\
	do {													\
		if (mode != GET_RET)								\
			redirect_start(g_capture_to_redirect[mode]);	\
		res_pointer->ret = (intptr_t)expr;					\
		res_pointer->out = NULL;							\
		if (mode != GET_RET)								\
		{													\
			res_pointer->out = redirect_read();				\
			redirect_stop();								\
		}													\
	} while (0)

#define capture_safe(mode, timeout, expr, capture_pointer)	\
	do {													\
		t_context	ctx;									\
															\
		fork_init(&ctx, timeout);							\
		if (ctx.child_pid > 0)								\
			capture_parent(&ctx, capture_pointer);			\
		else												\
		{													\
			t_capture_res capture_res = {0};				\
			capture(mode, expr, &capture_res);				\
			capture_child(&ctx, &capture_res);				\
		}													\
	} while (0)

#endif
