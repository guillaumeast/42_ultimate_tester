#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "error_priv.h"
#include "print_wrapper_pub.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static inline void	wait_for_child(int *status, t_set *set);
static inline void	handle_timeout(t_set *set);
static inline void	handle_crash(t_set *set, int status);

static t_set	*s_current_set;

void	set_run_parent(t_set *set)
{
	int		status;

	s_current_set = set;
	wait_for_child(&status, set);

	if (timeout_is_triggered() || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
		handle_timeout(set);
	else if (set->result.status.crash_address || WIFSIGNALED(status))
		handle_crash(set, status);
	else
		logs_print_h2();

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

	waitpid(g_context.child_pid, status, 0);
}

static inline void	handle_timeout(t_set *set)
{
	set->result.timed++;
	set->result.status.type = TIMED;
	set->result.status.timeout = set->timeout;

	logs_print_indicator(&set->result.status);
	logs_print_h2();

	print_stdout(" %s%s %s%s %stimed out (%zus)%s\n", GREY, EMJ_ARW_DR, RED, set->name, YELLOW, set->timeout, NONE);
}

static inline void	handle_crash(t_set *set, int status)
{
	set->result.crashed++;
	set->result.status.type = CRASHED;
	set->result.status.sig = WTERMSIG(status);

	logs_print_indicator(&set->result.status);
	logs_print_h2();

	print_stdout(" %s%s %s%s %s%s %sat %s%s\n", \
		GREY, EMJ_ARW_DR, \
		RED, set->name, YELLOW, format_status(&set->result.status), \
		GREY, format_addr(set->result.status.crash_address), NONE);
}
