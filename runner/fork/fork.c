#define __FUT_INSIDE__
#include "fork_priv.h"
#include "timeout_priv.h"
#undef __FUT_INSIDE__

#include <unistd.h>

t_error	fork_init(t_context *context, size_t timeout)
{
	context->child_pid = -1;
	context->result_pipe[0] = -1;
	context->result_pipe[1] = -1;
	context->sync_pipe[0] = -1;
	context->sync_pipe[1] = -1;

	if (pipe(context->result_pipe) == -1)
		return (RESULT_PIPE_CREATION_FAILED);
	if (pipe(context->sync_pipe) == -1)
	{
		fork_clear(context);
		return (SYNC_PIPE_CREATION_FAILED);
	}

	context->timeout = timeout;

	context->child_pid = fork();
	if (context->child_pid < 0)
		return (FORK_FAILED);

	return (NO_ERROR);
}

t_error	fork_init_parent(t_context *context)
{
	t_error	error;
	bool	ready;

	close(context->result_pipe[1]);
	close(context->sync_pipe[0]);

	error = timeout_init(context->child_pid, context->timeout);
	if (error != NO_ERROR)
	{
		kill(context->child_pid, SIGKILL);
		return (error);
	}

	ready = 1;
	write(context->sync_pipe[1], &ready, sizeof ready);
	close(context->sync_pipe[1]);
	return (NO_ERROR);
}

t_error	fork_init_child(t_context *context)
{
	bool	ready;

	close(context->result_pipe[0]);
	close(context->sync_pipe[1]);

	if (read(context->sync_pipe[0], &ready, sizeof ready) != sizeof ready)
		return (SYNC_PIPE_READ_FAILED);

	close(context->sync_pipe[0]);
	return (NO_ERROR);
}

void	fork_clear(t_context *context)
{
	if (context->result_pipe[0] != -1)
	{
		close(context->result_pipe[0]);
		context->result_pipe[0] = -1;
	}
	if (context->result_pipe[1] != -1)
	{
		close(context->result_pipe[1]);
		context->result_pipe[1] = -1;
	}
	if (context->sync_pipe[0] != -1)
	{
		close(context->sync_pipe[0]);
		context->sync_pipe[0] = -1;
	}
	if (context->sync_pipe[1] != -1)
	{
		close(context->sync_pipe[1]);
		context->sync_pipe[1] = -1;
	}
	
	timeout_cancel();
	context->timeout = 0;
	context->child_pid = -1;
}
