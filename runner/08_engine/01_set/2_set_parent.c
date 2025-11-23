#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "error_priv.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static inline void	wait_for_child(int *status, t_set *set);

static t_set	*s_current_set;

void	set_run_parent(t_set *set)
{
	int		status;

	s_current_set = set;
	wait_for_child(&status, set);
	logs_print_h2();

	if (timeout_is_triggered() || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
	{
		set->result.timed++;
		set->result.status.timeout = set->timeout;

		logs_print_h1("%s%s %stimed out (%zus)%s\n", \
			RED, set->name, YELLOW, set->timeout, NONE);
	}
	else if (set->result.status.crash_address || WIFSIGNALED(status))
	{
		set->result.crashed++;
		set->result.status.sig = WTERMSIG(status);
		logs_print_h1("%s%s %s%s %sat %s%s\n", \
			RED, set->name, YELLOW, format_status(&set->result.status), \
			GREY, format_addr(set->result.status.crash_address), NONE);
	}
	result_compute(&set->result);
	result_add(&set->result, &g_result);
	fork_cleanup();
}

static inline void	wait_for_child(int *status, t_set *set)
{
	t_message	message;

	while (message_receive(g_context.pipe_to_child, &message))
	{
		switch (message.type)
		{
			case RESULT:
				logs_print_indicator(&message.data.result.status);
				result_add(&message.data.result, &set->result);
				break;
			case CRASH:
				set->result.status.crash_address = message.data.crash_addr;
				break;
			case LOG:
				logs_store_h2("%s", message.data.log);
				break;
			default: exit_if(true, SET_UNKNOWN_MESSAGE_TYPE);
		}
	}

	waitpid(s_context.child_pid, status, 0);
}
