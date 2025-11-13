#include "print_priv.h"
#include "timeout_priv.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

static inline t_error	init_parent(t_set *set, pid_t child_pid);
static inline t_error	init_child(t_set *set);
static inline void	run_parent(pid_t child_pid, void *set);
static inline void	run_set_child(void *set);

t_result				g_result;
static int				sync_pipe[2] = { -1, -1 };
static int				result_pipe[2] = { -1, -1 };
volatile sig_atomic_t	set_timeout_triggered = false;

t_error	run_set(t_set *set)
{
	pid_t	child_pid;

	print_set_title(set);
	set->status = RUNNING;

	if (pipe(result_pipe) == -1 || pipe(sync_pipe) == -1)
		return (PIPE_ERR);

	child_pid = fork();
	if (child_pid < 0)
		return (FORK_ERR);

	if (child_pid > 0)
	{
		init_parent(set, child_pid);
		run_parent(set, child_pid);
	}
	else
	{
		init_child(set);
		run_set_child(set);
	}

	// TODO: compute result.total & result.status
	// process_result(&set->result, &set->status);
	return (NO_ERR);
}



static inline void	run_parent(pid_t child_pid, void *set)
{
	t_error	error;
	int		status;

	while (waitpid(child_pid, &status, 0) == -1 && errno == EINTR)
		continue;
	error = cancel_timeout();

	read(result_pipe[0], &g_current_set->result, sizeof(t_result));
	close(result_pipe[0]);

	if (set_timeout_triggered || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
	{
		g_current_set->result.timed++;
		g_current_set->result.total++;
		g_result.timed += g_current_set->result.timed;
		g_result.total += g_current_set->result.total;
		print_set_timed();
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		g_result.passed += g_current_set->result.passed;
		g_result.total += g_current_set->result.total;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		g_result.failed += g_current_set->result.failed;
		g_result.total += g_current_set->result.total;
	}
	else if (WIFSIGNALED(status))
	{
		g_current_set->result.crashed++;
		g_current_set->result.total++;
		g_result.crashed += g_current_set->result.crashed;
		g_result.total += g_current_set->result.total;
		print_set_crashed();
	}

	if (sigaction(SIGALRM, &old_action, NULL) == -1)
		ult_err_priv("sigaction failed to restore SIGALARM. Please report this issue.");
	current_child_pid = -1;
}

static inline void	run_set_child(void *set)
{
	close(result_pipe[0]);
	set->func();
	(void)!write(result_pipe[1], &g_current_set->result, sizeof(t_result));
	close(result_pipe[1]);
	if (g_current_set->result.passed == g_current_set->result.total)
	{
		print_set_passed(set);	// TODO: let the parent print
		exit(EXIT_SUCCESS);
	}
	else
	{
		print_set_failed(set);	// TODO: let the parent print
		exit(EXIT_FAILURE);
	}
}

/* TODO: put the above functions into separate common file (result.c ?) */

void	sum_results(t_result *dst, const t_result *src)
{
	dst->passed += src->passed;
	dst->failed += src->failed;
	dst->timed += src->timed;
	dst->crashed += src->crashed;
	dst->total += src->total;
}

t_status	get_status(t_result *result)
{
	if (result->passed == result->total)
		return (PASSED);
	if (result->failed > 0)
		return (FAILED);
	if (result->timed > 0)
		return (TIMED);
	if (result->crashed > 0)
		return (CRASHED);
	return (DONE);
}
