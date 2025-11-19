#ifndef ULT_CAPTURE_PUB_H
#define ULT_CAPTURE_PUB_H

#include "fork_pub.h"
#include "redirect_pub.h"
#include "status_pub.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef enum e_capture_mode
{
	RET,
	OUT,
	ERR,
	BOTH,
	RET_OUT,
	RET_ERR,
	RET_BOTH,
}	t_capture_mode;

static const t_redirect_mode g_capture_to_redirect[] = {
	[RET]		= -1,
    [OUT]       = R_STDOUT,
    [ERR]       = R_STDERR,
    [BOTH]      = R_BOTH,
    [RET_OUT]   = R_STDOUT,
    [RET_ERR]   = R_STDERR,
    [RET_BOTH]  = R_BOTH
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

#define __type_is_void(expr) __builtin_types_compatible_p(__typeof__(expr), void)
#define __expr_or_zero(expr) __builtin_choose_expr(__type_is_void(expr), 0, (expr))
#define CAP_VALUE(expr, dest) ({ (dest) = (intptr_t)(__expr_or_zero(expr)); 0; })
#define CAP_VOID(expr) ({ (void)(expr); 0; })
#define CAP_DISPATCH(expr, dest) \
	__builtin_choose_expr(__type_is_void(expr), \
		CAP_VOID(expr), \
		CAP_VALUE(expr, dest))

#define capture(mode, time_out, expr, capture_var_name)			\
	do {														\
		t_context	ctx;										\
																\
		memset(&capture_var_name, 0, sizeof(capture_var_name));	\
		capture_var_name.status.timeout = time_out;				\
		_fut_fork_init(&ctx, false, time_out);					\
		if (ctx.child_pid > 0)									\
			_fut_capture_parent(&ctx, &capture_var_name);		\
		else													\
		{														\
			t_capture_res capture_res = {0};					\
			if (mode != RET)								\
				redirect_start(g_capture_to_redirect[mode]);	\
			CAP_DISPATCH(expr, capture_res.ret);				\
			if (__type_is_void(expr))							\
				capture_res.ret = 0;							\
			if (mode != RET)								\
			{													\
				capture_res.out = redirect_read();				\
				redirect_stop();								\
			}													\
			_fut_capture_child(&ctx, &capture_res);				\
		}														\
	} while (0)

#endif
