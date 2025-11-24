#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "error_priv.h"
#include "messages_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

static inline void	wait_for_child(int *status, t_result *result);

void	_memcheck_parent(const char *expr)
{
	int			status;
	t_result	result = {0};

	wait_for_child(&status, &result);

	if (timeout_is_triggered())
	{
		result.timed++;
		result.status.type = TIMED;
		result.status.timeout = g_context.child_timeout;
		logs_print_indicator(&result.status);
		send_incorrect_status(expr, &result.status, NULL);
	}
	else if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
	{
		if (WIFSIGNALED(status))
			result.status.sig = WTERMSIG(status);

		result.crashed++;
		send_incorrect_status(expr, &result.status, NULL);
	}

	result_compute(&result);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);
	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_result *result)
{
	t_message	message;

	while (message_receive(g_context.pipe_to_child, &message))
	{
		switch (message.type)
		{
			case RESULT:
				logs_print_indicator(&message.data.result.status);
				result_add(&message.data.result, result);
				break;
			case CRASH:
				result->status.type = CRASHED;
				result->status.crash_address = message.data.crash_addr;
				logs_print_indicator(&result->status);
				break;
			case LOG:
				message_send(g_context.pipe_to_parent, LOG, &message.data);
				break;
			default: exit_if(true, SET_UNKNOWN_MESSAGE_TYPE);
		}
	}

	waitpid(g_context.child_pid, status, 0);
}
