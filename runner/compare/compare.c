#include "compare_pub.h"
#include "fork_priv.h"

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
	t_error	error;

	error = NO_ERR;
	error = fork_init_parent(context);
	if (error != NO_ERR)
		return (error);

	// TODO: waitpid + process results
	ult_print("Compare_parent => %s%s vs %s%s\n", data->fn1.name, data->fn1.args, data->fn2.name, data->fn2.args);

	fork_clear(context);
	return (error);
}

t_error	comp_init_child_priv(t_context *context, t_compare *data)
{
	t_error	error;

	error = NO_ERR;

	error = fork_init_child(context);
	if (error != NO_ERR)
		return (error);

	if (data->mode == COMP_OUT || data->mode == COMP_RET_OUT)
		error = redirect_start(R_STDOUT);
	if (error == NO_ERR && (data->mode == COMP_ERR || data->mode == COMP_RET_ERR))
		error = redirect_start(R_STDERR);
	if (error == NO_ERR && (data->mode == COMP_BOTH || data->mode == COMP_RET_BOTH))
		error = redirect_start(R_BOTH);
	return (error);
}

void	comp_child_priv(t_context *context, t_compare *data)
{
	int exit_value;

	if (data->mode != COMP_RET)
		redirect_stop();

	/* ------ TODO: process results and set exit_value to EXIT_SUCCESS or EXIT_FAILURE ------ */
	ult_print("Comp_child:\n");
	ult_print("    => %s%s = %s (%i)\n", data->fn1.name, data->fn1.args, data->fn1.out, (int)data->fn1.ret);
	ult_print("    => %s%s = %s (%i)\n", data->fn2.name, data->fn2.args, data->fn2.out, (int)data->fn2.ret);
	exit_value = EXIT_SUCCESS;
	/* -------------------------------------------------------------------------------------- */

	(void)fork_clear(context);
	exit(exit_value);
}
