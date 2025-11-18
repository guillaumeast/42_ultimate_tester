#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#include "assert_pub.h"
#include "compare_int.h"
#undef __FUT_ENGINE_INSIDE__
#include "print_priv.h"
#undef __FUT_INSIDE__

#include <inttypes.h>

static inline t_status	check_status(t_assert *assert);
static inline t_status	check_ret(t_assert *assert);
static inline t_status	check_out(t_assert *assert);
static inline void		print_status_fail(const char *expr_name, t_status *status);
static inline void		print_ret_fail(t_assert *assert);

// TODO: merge check_assert_eq() and check_assert_neq()
// TODO: split into check_status.c + check_ret.c + check_out.c (they implement both eq and neq versions and choose which one to execute depending on assert->eq value)
t_status	check_assert_neq(t_assert *assert)
{
	t_status	status_res = {0};
	t_status	ret_res = {0};
	t_status	out_res = {0};
	t_status	final_res = {0};
	
	status_res = check_status(assert);
	if (status_res.type != PASSED)
		return (status_res);

	ret_res.type = PASSED;
	if (assert->mode != GET_OUT && assert->mode != GET_ERR && assert->mode != GET_BOTH)
		ret_res = check_ret(assert);

	out_res.type = PASSED;
	if (assert->mode != GET_RET)
		out_res = check_out(assert);

	if (ret_res.type == PASSED && out_res.type == PASSED)
		final_res.type = PASSED;
	else
		final_res.type = FAILED;

	return (final_res);
}

// TODO: refactor with new `t_status handle_status_fail(const char *expr_name, t_status *status)` func
static inline t_status	check_status(t_assert *assert)
{
	t_status	status = {0};

	status.type = PASSED;
	if (assert->got->status.type != DONE || assert->exp->status.type != DONE)
	{
		if (assert->got->status.type == CRASHED)
		{
			status.type = CRASHED;
			status.sig = assert->got->status.sig;
			print_stderr("%s    %s %s CRASHED%s: ", RED, EMJ_ARW_DR, EMJ_CRSH_Y, NONE);
			print_status_fail(assert->got_name, &assert->got->status);
		}
		else if (assert->got->status.type == TIMED)
		{
			status.type = TIMED;
			status.timeout = assert->got->status.timeout;
			print_stderr("%s    %s %s TIMED%s:   ", RED, EMJ_ARW_DR, EMJ_TIMD, NONE);
			print_status_fail(assert->got_name, &assert->got->status);
		}
		else if (assert->exp->status.type == CRASHED)
		{
			status.type = CRASHED;
			status.sig = assert->exp->status.sig;
			print_stderr("%s    %s %s CRASHED%s: ", RED, EMJ_ARW_DR, EMJ_CRSH_Y, NONE);
			print_status_fail(assert->exp_name, &assert->exp->status);
		}
		else if (assert->exp->status.type == TIMED)
		{
			status.type = TIMED;
			status.timeout = assert->exp->status.timeout;
			print_stderr("%s    %s %s TIMED%s:   ", RED, EMJ_ARW_DR, EMJ_TIMD, NONE);
			print_status_fail(assert->exp_name, &assert->exp->status);
		}
	}
	return (status);
}

static inline t_status	check_ret(t_assert *assert)
{
	t_status	status = {0};

	status.type = PASSED;
	if (assert->format == F_STRING)
	{
		if (compare_strings((char *)assert->got->ret, (char *)assert->exp->ret))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (assert->format == F_STRUCT)
	{
		if (compare_structs((void *)assert->got->ret, (void *)assert->exp->ret, assert->ret_size))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (compare_intptr_t(assert->got->ret, assert->exp->ret))
	{
		status.type = FAILED;
		print_ret_fail(assert);
	}
	return (status);
}

static inline t_status	check_out(t_assert *assert)
{
	t_status	status = {0};

	if (!compare_strings(assert->got->out, assert->exp->out))
		status.type = PASSED;
	else
	{
		status.type = FAILED;
		print_stderr("%s    %s %s FAILED%s:  ", RED, EMJ_ARW_DR, EMJ_FAIL, NONE);
		print_stderr("[%s%s%s] and [%s%s%s] ", RED, assert->got_name, NONE, RED, assert->exp_name, NONE);
		print_stderr("%soutputed%s the same value ", YELLOW, NONE);
		print_stderr("[%s%s%s]\n", RED, assert->exp->out, NONE);
	}
	return (status);
}

static inline void	print_status_fail(const char *expr_name, t_status *status)
{
	char status_buffer[STATUS_BUFFER_SIZE];
	
	status_format(status, status_buffer, STATUS_BUFFER_SIZE);
	print_stderr("[%s%s%s] has [%s%s%s]\n", RED, expr_name, NONE, RED, status_buffer, NONE);
}

static inline void	print_ret_fail(t_assert *assert)
{
	print_stderr("%s    %s %s FAILED%s:  ", RED, EMJ_ARW_DR, EMJ_FAIL, NONE);
	print_stderr("[%s%s%s] and [%s%s%s] ", RED, assert->got_name, NONE, RED, assert->exp_name, NONE);
	print_stderr("%sreturned%s the same value ", YELLOW, NONE);

	if (assert->format == F_STRUCT)
		print_stderr("[%ssame struct content%s]\n", RED, NONE);
	else if (assert->format == F_STRING)
		print_stderr("[%s%s%s]\n", RED, (char *)assert->exp->ret, NONE);
	else if (assert->format == F_CHAR)
		print_stderr("[%s%c%s]\n", RED, (char)assert->exp->ret, NONE);
	else if (assert->format == F_SIGNED)
		print_stderr("[%s%" PRIdPTR "%s]\n", RED, (intptr_t)assert->exp->ret, NONE);
	else if (assert->format == F_UNSIGNED)
		print_stderr("[%s%" PRIuPTR "%s]\n", RED, (uintptr_t)assert->exp->ret, NONE);
	else
		print_stderr("[%s%" PRIxPTR "%s]\n", RED, (uintptr_t)assert->exp->ret, NONE);
}
