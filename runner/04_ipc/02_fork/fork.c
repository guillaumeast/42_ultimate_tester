#define __FUT_INSIDE__
#define __FUT_IPC_INSIDE__
#include "fork_priv.h"
#include "error_priv.h"
#include "timeout_ipc.h"
#undef __FUT_IPC_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static inline void	fork_init_parent(t_context *context);
static inline void	fork_init_child(t_context *context);

void	_fut_fork_init(t_context *context, size_t timeout)
{
	context->child_pid = -1;
	context->result_pipe[0] = -1;
	context->result_pipe[1] = -1;
	context->sync_pipe[0] = -1;
	context->sync_pipe[1] = -1;

	exit_if(pipe(context->result_pipe) == -1, RESULT_PIPE_CREATION_FAILED);
	exit_if(pipe(context->sync_pipe) == -1, SYNC_PIPE_CREATION_FAILED);

	context->timeout = timeout;
	context->child_pid = fork();
	exit_if(context->child_pid < 0, FORK_FAILED);
	if (context->child_pid > 0)
		fork_init_parent(context);
	else
	 	fork_init_child(context);
}

void	fork_cleanup(t_context *context)
{
	if (!context)
		return ;
	
	if (context->result_pipe[0] != -1)
		close(context->result_pipe[0]);
	if (context->result_pipe[1] != -1)
		close(context->result_pipe[1]);
	if (context->sync_pipe[0] != -1)
		close(context->sync_pipe[0]);
	if (context->sync_pipe[1] != -1)
		close(context->sync_pipe[1]);

	context->result_pipe[0] = -1;
	context->result_pipe[1] = -1;
	context->sync_pipe[0] = -1;
	context->sync_pipe[1] = -1;
	
	timeout_cancel();
	context->timeout = 0;

	if (context->child_pid > 0)
		kill(context->child_pid, SIGKILL);
	if (context->child_pid != -1)
		context->child_pid = -1;
}

static inline void	fork_init_parent(t_context *context)
{
	bool	ready;

	close(context->result_pipe[1]);
	close(context->sync_pipe[0]);

	timeout_init(context->child_pid, context->timeout);

	ready = 1;
	write(context->sync_pipe[1], &ready, sizeof ready);
	close(context->sync_pipe[1]);
}

static inline void	fork_init_child(t_context *context)
{
	bool	ready;

	close(context->result_pipe[0]);
	close(context->sync_pipe[1]);

	if (read(context->sync_pipe[0], &ready, sizeof ready) != sizeof ready)
		exit_if(true, SYNC_PIPE_READ_FAILED);

	close(context->sync_pipe[0]);
}
