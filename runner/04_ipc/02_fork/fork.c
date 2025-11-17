#define __FUT_INSIDE__
#include "fork_pub.h"
#define __FUT_IPC_INSIDE__
#include "timeout_ipc.h"
#undef __FUT_IPC_INSIDE__
#include "error_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

static inline void	fork_init_parent(t_context *context);
static inline void	fork_init_child(t_context *context);

static __thread t_context	*s_current_context;

void	fork_init(t_context *context, size_t timeout)
{
	s_current_context = context;
	atexit(fork_clear);

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

void	fork_clear(void)
{
	if (!s_current_context)
		return ;
	
	if (s_current_context->result_pipe[0] != -1)
		close(s_current_context->result_pipe[0]);
	if (s_current_context->result_pipe[1] != -1)
		close(s_current_context->result_pipe[1]);
	if (s_current_context->sync_pipe[0] != -1)
		close(s_current_context->sync_pipe[0]);
	if (s_current_context->sync_pipe[1] != -1)
		close(s_current_context->sync_pipe[1]);

	s_current_context->result_pipe[0] = -1;
	s_current_context->result_pipe[1] = -1;
	s_current_context->sync_pipe[0] = -1;
	s_current_context->sync_pipe[1] = -1;
	
	timeout_cancel();
	s_current_context->timeout = 0;

	if (s_current_context->child_pid > 0)
		kill(s_current_context->child_pid, SIGKILL);
	if (s_current_context->child_pid != -1)
		s_current_context->child_pid = -1;
}

static inline void	fork_init_parent(t_context *context)
{
	t_error	error;
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
