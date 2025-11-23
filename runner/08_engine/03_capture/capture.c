#define __FUT_INSIDE__
#include "capture_pub.h"
#include "error_priv.h"
#include "process_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline void	read_result(t_capture *capture);

void	_capture_parent(t_capture *capture)
{
	int		status;
	void	*crash_address;
	size_t	bytes;

	// TODO: read and wait (cf memcheck)
	waitpid(g_context.child_pid, &status, 0);

	if (timeout_is_triggered())
		capture->status.type = TIMED;
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		read_result(capture);
		capture->status.type = DONE;
	}
	else
	{
		capture->status.type = CRASHED;
		if (WIFSIGNALED(status))
			capture->status.sig = WTERMSIG(status);
	}
	fork_cleanup();
}

void	_capture_child(t_capture_res *res)
{
	size_t	len;

	// TODO: use message module (!!! Don't limit output size -> make message module ok with that !!!)
	write(g_context.pipe_to_parent[1], &res->ret, sizeof res->ret);

	if (res->out)
		len = strlen(res->out);
	else
	 	len = 0;
	// TODO: use message module
	write(g_context.result_pipe[1], &len, sizeof len);
	write(g_context.result_pipe[1], res->out, len);

	fork_cleanup();
	exit (EXIT_SUCCESS);
}

static inline void	read_result(t_capture *capture)
{
	size_t	len;

	// TODO: use message module
	read(g_context.result_pipe[0], &capture->ret, sizeof capture->ret);
	read(g_context.result_pipe[0], &len, sizeof len);

	capture->out = malloc(len + 1);
	exit_if(!capture->out, NOT_ENOUGH_MEMORY);
	read(g_context.result_pipe[0], capture->out, len);
	capture->out[len] = '\0';
}
