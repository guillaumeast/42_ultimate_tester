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

static size_t		s_fork_depth = 0;

static inline void	fork_init_parent(t_context *prev_context, int new_pipe[2]);
static inline void	fork_init_child(t_context *prev_context, int new_pipe[2]);

void	_fork_init(size_t timeout)
{
	t_context	previous_context;
	int			new_pipe[2];

	previous_context = g_context;
	context_init();

	exit_if(pipe(new_pipe) == -1, PIPE_CREATION_FAILED);
	timeout_init(timeout);

	g_context.child_pid = fork();
	exit_if(g_context.child_pid < 0, FORK_FAILED);
	
	if (g_context.child_pid > 0)
		fork_init_parent(&previous_context, new_pipe);
	else
	 	fork_init_child(&previous_context, new_pipe);
}

static inline void	fork_init_parent(t_context *prev_context, int new_pipe[2])
{
	bool	ready;

	if (s_fork_depth == 0)
	{
		context_set_target_pid(-g_context.child_pid);
		context_init_sigint_handler();
	}
	else
		context_set_target_pid(g_context.child_pid);

	g_context.has_parent = prev_context->has_parent;
	g_context.has_child = true;
	if (g_context.has_parent)
	{
		g_context.pipe_to_parent[0] = prev_context->pipe_to_parent[0];
		g_context.pipe_to_parent[1] = prev_context->pipe_to_parent[1];
	}
	g_context.pipe_to_child[0] = new_pipe[0];
	g_context.pipe_to_child[1] = new_pipe[1];

	timeout_start();
	ready = 1;
	write(g_context.pipe_to_child[1], &ready, sizeof ready);
	close(g_context.pipe_to_child[1]);
	g_context.pipe_to_child[1] = -1;
}

static inline void	fork_init_child(t_context *prev_context, int new_pipe[2])
{
	bool	ready;

	s_fork_depth++;
	if (s_fork_depth == 1)
		setpgid(0, 0);

	g_context.has_parent = true;
	g_context.has_child = false;
	g_context.pipe_to_parent[0] = new_pipe[0];
	g_context.pipe_to_parent[1] = new_pipe[1];

	stacktrace_init(g_context.pipe_to_parent[1]);

	read(g_context.pipe_to_parent[0], &ready, sizeof ready);
	close(g_context.pipe_to_parent[0]);
	g_context.pipe_to_parent[0] = -1;
}

void	fork_cleanup(void)
{
	timeout_cancel();

	if (g_context.has_child == false)
	{
		close(g_context.pipe_to_parent[1]);
		g_context.pipe_to_parent[1] = -1;
	}
	if (g_context.has_child)
	{
		close(g_context.pipe_to_child[0]);
		g_context.pipe_to_child[0] = -1;
	}

	g_context.has_child = false;
	if (s_fork_depth == 0)
		context_cancel_sigint_handler();
}
