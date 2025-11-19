#include "print_pub.h"
#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "set_int_set.h"
#include "timeout_priv.h"
#include "print_priv.h"
#include "fork_priv.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

static inline void	run_parent(t_set *set);
static inline void	read_results_from_child(int *status, t_set *set);
static inline void	run_child(t_set *set);

t_result	g_result;
t_context	s_context;

void	set_run(t_set *set)
{
	set_print_title(set);
	set->result.status.type = RUNNING;

	_fut_fork_init(&s_context, set->timeout);
	if (s_context.child_pid > 0)
		run_parent(set);
	else
		run_child(set);

	result_add(&set->result, &g_result);
	set_print_result(set);
}

static inline void	run_parent(t_set *set)
{
	int	status;

	read_results_from_child(&status, set);

	if (g_timeout_triggered || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
	{
		set->result.timed++;
		set->result.status.timeout = set->timeout;

		print_stderr("%s%sTIMED %s(set exceeded %zus)%s\n", \
			RED, EMJ_TIMD, YELLOW, set->timeout, NONE);
	}
	else if (WIFSIGNALED(status))
	{
		set->result.crashed++;
		set->result.status.sig = WTERMSIG(status);

		print_stderr("%s%sCRASHED %s(set crashed: %s)%s\n", \
			RED, EMJ_CRSH_Y, YELLOW, \
			status_sig(&set->result.status), NONE);
	}

	result_compute(&set->result);
	fork_cleanup(&s_context);
}

static inline void	read_results_from_child(int *status, t_set *set)
{
	int			flags;
	ssize_t		bytes;
	t_result	new_result;
	pid_t		pid;

	flags = fcntl(s_context.result_pipe[0], F_GETFL);
	fcntl(s_context.result_pipe[0], F_SETFL, flags | O_NONBLOCK);
	
	while (1)
	{
		while ((bytes = read(s_context.result_pipe[0], &new_result, sizeof(t_result))) > 0)
			result_add(&new_result, &set->result);
		if (bytes == 0)
			break;
		if (bytes == -1 && errno != EAGAIN)
			break;

		pid = waitpid(s_context.child_pid, status, WNOHANG);
		if (pid == s_context.child_pid)
			break;
		if (pid == -1 && errno != EINTR)
			break;

		usleep(200);
	}
}

static inline void	run_child(t_set *set)
{
	set->func();

	fork_cleanup(&s_context);
	exit(EXIT_SUCCESS);
}

// Called by assert module (inside set_child)
void	set_add_result(t_result *result)
{
	(void)write(s_context.result_pipe[1], result, sizeof(t_result));
}
