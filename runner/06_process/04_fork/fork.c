#define __FUT_INSIDE__
#define __FUT_PROCESS_INSIDE__
#include "context_process.h"
#include "error_priv.h"
#include "fork_priv.h"
#include "stacktrace_process.h"
#include "timeout_process.h"
#undef __FUT_PROCESS_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

static size_t	s_fork_depth = 0;

static inline void	fork_init_parent(t_context *context);
static inline void	fork_init_child(t_context *context);

void	_fork_init(t_context *context, size_t timeout)
{
	exit_if(pipe(context->pipe) == -1, PIPE_CREATION_FAILED);
	timeout_init(context, timeout);

	context->child_pid = fork();
	exit_if(context->child_pid < 0, FORK_FAILED);
	
	if (context->child_pid > 0)
		fork_init_parent(context);
	else
	 	fork_init_child(context);
}

static inline void	fork_init_parent(t_context *context)
{
	bool				ready;

	if (s_fork_depth == 0)
	{
		context_set_target_pid(-context->child_pid);
		context_init_sigint_handler(context);
	}
	else
		context_set_target_pid(context->child_pid);

	timeout_start(context);

	ready = 1;
	write(context->pipe[1], &ready, sizeof ready);
	close(context->pipe[1]);
	context->pipe[1] = -1;
}

static inline void	fork_init_child(t_context *context)
{
	bool	ready;

	s_fork_depth++;
	if (s_fork_depth == 1)
		setpgid(0, 0);

	stacktrace_init();

	read(context->pipe[0], &ready, sizeof ready);
	close(context->pipe[0]);
	context->pipe[0] = -1;
}

void	fork_cleanup(t_context *context)
{
	if (!context)
		return ;
	
	timeout_cancel(context);

	if (context->pipe[0] != -1)
	{
		close(context->pipe[0]);
		context->pipe[0] = -1;
	}
	if (context->pipe[1] != -1)
	{
		close(context->pipe[1]);
		context->pipe[1] = -1;
	}

	if (s_fork_depth == 0)
		context_cancel_sigint_handler(context);
}
