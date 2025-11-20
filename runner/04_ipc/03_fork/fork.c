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

static size_t	s_fork_depth = 0;

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

static inline void	fork_init_parent(t_context *context)
{
	bool				ready;
	struct sigaction	new_action = {0};

	close(context->result_pipe[1]);
	close(context->sync_pipe[0]);

	if (s_fork_depth == 0)
	{
		handlers_set_target_pid(-context->child_pid);
		exit_if(sigemptyset(&new_action.sa_mask) == -1, SIGINT_HANDLER_SET_FAILED);
		new_action.sa_flags = SA_RESETHAND;
		new_action.sa_handler = sigint_handler;
		exit_if(sigaction(SIGINT, &new_action, NULL) == -1, SIGINT_HANDLER_SET_FAILED);
	}
	else
		handlers_set_target_pid(context->child_pid);

	timeout_init(context->timeout);

	ready = 1;
	write(context->sync_pipe[1], &ready, sizeof ready);
	close(context->sync_pipe[1]);
}

static inline void	fork_init_child(t_context *context)
{
	bool	ready;

	s_fork_depth++;
	if (s_fork_depth == 1)
		setpgid(0, 0);

	close(context->result_pipe[0]);
	close(context->sync_pipe[1]);

	if (read(context->sync_pipe[0], &ready, sizeof ready) != sizeof ready)
		exit_if(true, SYNC_PIPE_READ_FAILED);

	close(context->sync_pipe[0]);
}

void	fork_cleanup(t_context *context)
{
	struct sigaction action = {0};

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

	if (s_fork_depth == 0)
	{
		action.sa_handler = SIG_DFL;
		exit_if(sigaction(SIGINT, &action, NULL) == -1, SIGINT_HANDLER_CANCEL_FAILED);
	}
}

bool	fork_is_timeout_triggered(void)
{
	return (g_timeout_triggered);
}
