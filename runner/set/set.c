#include "fork_priv.h"
#include "print_priv.h"
#include "timeout_priv.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

static inline void		set_run_parent(t_context *context, t_set *set);
static inline void		set_run_child(t_context *context, t_set *set);

t_set							g_set;	// TODO: implement set* in assert.c
t_result						g_result;
extern volatile sig_atomic_t	g_timeout_triggered;

t_error	set_run(t_set *set)
{
	t_error		error;
	t_context	context;

	print_set_title(set);
	set->status = RUNNING;

	error = fork_init(&context, set->timeout);
	if (error != NO_ERR)
		return error;

	if (context.child_pid > 0)
	{
		error = fork_init_parent(&context);
		if (error != NO_ERR)
			return error;
		set_run_parent(&context, set);
	}
	else
	{
		error = fork_init_child(&context);
		if (error != NO_ERR)
			return error;
		set_run_child(&context, set);
	}

	// TODO: compute result.total & result.status
	// process_result(&set->result, &set->status);
	return (NO_ERR);
}

static inline void	set_run_parent(t_context *context, t_set *set)
{
	int		status;

	(void)set;	// TODO
	while (waitpid(context->child_pid, &status, 0) == -1 && errno == EINTR)
		continue;
	(void)timeout_cancel();

	read(context->result_pipe[0], &set->result, sizeof(t_result));
	fork_clear(context);

	if (g_timeout_triggered || (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM))
	{
		set->result.timed++;
		set->result.total++;
		g_result.timed += set->result.timed;
		g_result.total += set->result.total;
		print_set_timed();
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		g_result.passed += set->result.passed;
		g_result.total += set->result.total;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		g_result.failed += set->result.failed;
		g_result.total += set->result.total;
	}
	else if (WIFSIGNALED(status))
	{
		set->result.crashed++;
		set->result.total++;
		g_result.crashed += set->result.crashed;
		g_result.total += set->result.total;
		print_set_crashed();
	}
}

static inline void	set_run_child(t_context *context, t_set *set)
{
	set->func();

	(void)!write(context->result_pipe[1], &set->result, sizeof(t_result));

	if (set->result.passed == set->result.total)
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
