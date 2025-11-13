# include "fork_priv.h"
# include "timeout_priv.h"
# include <unistd.h>

static inline t_error	init_parent(t_fork_context *context, int sync_pipe[2]);
static inline t_error	init_child(t_fork_context *context, int sync_pipe[2]);

t_error process_fork(t_fork_context *context)
{
	t_error	error;
	int		sync_pipe[2];
	
	if (pipe(context->result_pipe) == -1 || pipe(sync_pipe) == -1)
		return (PIPE_ERR);
	context->child_pid = fork();
	if (context->child_pid < 0)
		return (FORK_ERR);
	if (context->child_pid > 0)
	{
		error = init_parent(context, sync_pipe);
		if (error != NO_ERR) return (error);
		error = context->parent_runner(context->child_pid, context->data);
		close(context->result_pipe[0]);
	}
	else
	{
		error = init_child(context, sync_pipe);
		if (error != NO_ERR) return (error);
		error = (context->child_runner(context->data));
		close(context->result_pipe[1]);
	}
	return (error);
}

static inline t_error	init_parent(t_fork_context *context, int sync_pipe[2])
{
	t_error	error;
	bool	ready;

	close(context->result_pipe[1]);
	close(sync_pipe[0]);
	error = setup_timeout(context->child_pid, context->timeout);
	if (error != NO_ERR)
	{
		kill(context->child_pid, SIGKILL);
		close(context->result_pipe[0]);
		close(sync_pipe[1]);
		return (error);
	}
	ready = 1;
	write(sync_pipe[1], &ready, sizeof ready);
	close(sync_pipe[1]);
	return (NO_ERR);
}

static inline t_error	init_child(t_fork_context *context, int sync_pipe[2])
{
	t_error	error;
	bool	ready;

	close(context->result_pipe[0]);
	close(sync_pipe[1]);
	if (read(sync_pipe[0], &ready, sizeof ready) != sizeof ready)
	{
		close(context->result_pipe[1]);
		close(sync_pipe[0]);
		return (PIPE_ERR);
	}
	close(sync_pipe[0]);
	return (NO_ERR);
}
