#include "compare_pub.h"
#include "fork_priv.h"
#include <errno.h>
#include <unistd.h>

t_error	comp_init_priv(t_context *cxt, size_t to, t_compare *cmp, t_comp_mode md, char *f1, char *f2, char *a1, char *a2)
{
	cmp->status = QUEUED;
	cmp->mode = md;
	cmp->fn1.name = f1;
	cmp->fn1.args = a1;
	cmp->fn1.ret = 0;
	cmp->fn1.out = NULL;
	cmp->fn2.name = f2;
	cmp->fn2.args = a2;
	cmp->fn2.ret = 0;
	cmp->fn2.out = NULL;

	return (fork_init(cxt, to));
}

t_error	comp_parent_priv(t_context *context, t_compare *data)
{
	int			status;
	t_error		error;
	t_result	res;

	error = NO_ERROR;
	error = fork_init_parent(context);
	if (error != NO_ERROR)
		return (error);

	// TODO: waitpid + process results
	ult_print("Compare_parent => %s%s vs %s%s\n", data->fn1.name, data->fn1.args, data->fn2.name, data->fn2.args);

	while (waitpid(context->child_pid, &status, 0) == -1 && errno == EINTR)
		continue;

	if (read(context->result_pipe[0], &res, sizeof(res)) == sizeof(res))
	{
		// TODO
		ult_print("Compare_parent => result.total = %zu\n", res.total);
	}

	fork_clear(context);
	return (error);
}

t_error	comp_init_child_priv(t_context *context, t_compare *data)
{
	t_error	error;

	error = NO_ERROR;

	error = fork_init_child(context);
	if (error != NO_ERROR)
		return (error);

	if (data->mode == COMP_OUT || data->mode == COMP_RET_OUT)
		error = redirect_start(R_STDOUT);
	if (error == NO_ERROR && (data->mode == COMP_ERR || data->mode == COMP_RET_ERR))
		error = redirect_start(R_STDERR);
	if (error == NO_ERROR && (data->mode == COMP_BOTH || data->mode == COMP_RET_BOTH))
		error = redirect_start(R_BOTH);
	// TODO: convert redirect_start return value to `t_error`
	if (error == true)
		error = NO_ERROR;
	else
	 	error = REDIRECT_START_FAILED;
	return (error);
}

void	comp_child_priv(t_context *context, t_compare *data)
{
	int			exit_value;

	if (data->mode != COMP_RET)
		redirect_stop();

	/* ------ TODO: process results and set exit_value to EXIT_SUCCESS or EXIT_FAILURE ------ */
	ult_print("Comp_child:\n");
	ult_print("    => %s%s = %s (%i)\n", data->fn1.name, data->fn1.args, data->fn1.out->data, (int)data->fn1.ret);
	ult_print("    => %s%s = %s (%i)\n", data->fn2.name, data->fn2.args, data->fn2.out->data, (int)data->fn2.ret);
	t_result res = {1, 1, 0, 0, 0};

	(void)!write(context->result_pipe[1], &res, sizeof(res));
	exit_value = EXIT_SUCCESS;
	/* -------------------------------------------------------------------------------------- */

	(void)fork_clear(context);
	exit(exit_value);
}
