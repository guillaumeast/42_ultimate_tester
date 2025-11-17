#define __FUT_INSIDE__
#include "capture_pub.h"
#include "error_priv.h"
#include "timeout_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline void	read_result(t_context *ctx, t_capture *capture);

void	capture_parent(t_context *ctx, t_capture *capture)
{
	int		status;

	memset(capture, 0, sizeof(*capture));
	waitpid(ctx->child_pid, &status, 0);
	
	if (g_timeout_triggered)
		capture->timed = true;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		read_result(ctx, capture);
	else
	{
		capture->crashed = true;
		capture->signal = WTERMSIG(status);
	}

	fork_clear();
}

void	capture_child(t_context *ctx, t_capture_res *res)
{
	size_t	len;

	write(ctx->result_pipe[1], &res->ret, sizeof res->ret);

	len = strlen(res->out);
	write(ctx->result_pipe[1], &len, sizeof len);
	write(ctx->result_pipe[1], res->out, len);

	fork_clear();
	exit (EXIT_SUCCESS);
}

static inline void	read_result(t_context *ctx, t_capture *capture)
{
	size_t	len;

	read(ctx->result_pipe[0], &capture->ret, sizeof capture->ret);
	read(ctx->result_pipe[0], &len, sizeof len);

	capture->out = malloc(len + 1);
	exit_if(!capture->out, CAPTURE_NOT_ENOUGH_MEMORY);
	read(ctx->result_pipe[0], capture->out, len);
	capture->out[len] = '\0';

	capture->ok = true;
}
