#define __FUT_INSIDE__
#include "capture_pub.h"
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline void	wait_for_child(int *status, t_capture *capture);
static inline void	read_ret(t_capture *capture);
static inline void	read_out(t_capture *capture);
static inline void	read_crash(t_capture *capture);

void	_capture_parent(t_capture *capture)
{
	int		status;
	void	*crash_address;
	size_t	bytes;

	wait_for_child(&status, capture);

	if (timeout_is_triggered())
		capture->status.type = TIMED;
	else if (capture->status.crash_address || !WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		capture->status.type = CRASHED;
		if (WIFSIGNALED(status))
			capture->status.sig = WTERMSIG(status);
	}

	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_capture *capture)
{
	t_message		first_message;
	t_message_type	type;
	size_t			len;

	len = 0;
	while (message_read_type(g_context.pipe_to_child, &type))
	{
		switch (type)
		{
			case RETURN_VALUE:	read_ret(capture); break;
			case CUSTOM:		read_out(capture); break;
			case CRASH:			read_crash(capture); break;
			default:			exit_if(true, MESSAGE_UNKNOWN_TYPE);
		}
	}
	waitpid(g_context.child_pid, status, 0);
}

static inline void	read_ret(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);
	exit_if(len != sizeof capture->ret, MESSAGE_INVALID_LEN);

	(void)message_read_data(g_context.pipe_to_child, &capture->ret, sizeof capture->ret);
}

static inline void	read_out(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);

	capture->out = malloc(len + 1);
	exit_if(!capture->out, NOT_ENOUGH_MEMORY);

	(void)message_read_data(g_context.pipe_to_child, capture->out, len);
	capture->out[len] = '\0';
}

static inline void	read_crash(t_capture *capture)
{
	size_t	len;

	len = 0;
	(void)message_read_len(g_context.pipe_to_child, &len);
	exit_if(len != sizeof capture->status.crash_address, MESSAGE_INVALID_LEN);

	(void)message_read_data( \
		g_context.pipe_to_child, \
		&capture->status.crash_address, \
		sizeof capture->status.crash_address \
	);
}
