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
static inline void		print_status_fail(t_assert *assert);
static inline void		print_ret_fail(t_assert *assert);

t_status	check_assert_eq(t_assert *assert)
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

static inline t_status	check_status(t_assert *assert)
{
	t_status	status = {0};

	status.type = PASSED;
	if (assert->got->status.type != DONE)
	{
		if (compare_status(&assert->got->status, &assert->exp->status))
			status.type = PASSED;
		else if (assert->got->status.type == CRASHED)
		{
			status.type = CRASHED;
			status.sig = assert->got->status.sig;
			print_stderr("%s    %s %s CRASHED%s: ", RED, EMJ_ARW_DR, EMJ_CRSH_Y, NONE);
			print_status_fail(assert);
		}
		else if (assert->got->status.type == TIMED)
		{
			status.type = TIMED;
			status.timeout = assert->got->status.timeout;
			print_stderr("%s    %s %s TIMED%s:   ", RED, EMJ_ARW_DR, EMJ_TIMD, NONE);
			print_status_fail(assert);
		}
		else
		{
			status.type = FAILED;
			print_stderr("%s    %s %s FAILED%s:  ", RED, EMJ_ARW_DR, EMJ_TIMD, NONE);
			print_status_fail(assert);
		}
	}
	else if (assert->exp->status.type != DONE)
	{
		status.type = FAILED;
		print_stderr("%s    %s %s FAILED%s:  ", RED, EMJ_ARW_DR, EMJ_FAIL, NONE);
		print_status_fail(assert);
	}
	return (status);
}

static inline t_status	check_ret(t_assert *assert)
{
	t_status	status = {0};

	status.type = PASSED;
	if (assert->format == F_STRING)
	{
		if (!compare_strings((char *)assert->got->ret, (char *)assert->exp->ret))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (assert->format == F_STRUCT)
	{
		if (!compare_structs((void *)assert->got->ret, (void *)assert->exp->ret, assert->ret_size))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (!compare_intptr_t(assert->got->ret, assert->exp->ret))
	{
		status.type = FAILED;
		print_ret_fail(assert);
	}
	return (status);
}

static inline t_status	check_out(t_assert *assert)
{
	t_status	status = {0};

	if (compare_strings(assert->got->out, assert->exp->out))
		status.type = PASSED;
	else
	{
		status.type = FAILED;
		print_stderr("%s    %s %s FAILED%s:  [%s%s%s] ", RED, EMJ_ARW_DR, EMJ_FAIL, NONE, RED, assert->got_name, NONE);
		print_stderr("%soutputed%s [%s%s%s] ", YELLOW, NONE, RED, assert->got->out, NONE);
		print_stderr("instead of [%s%s%s]\n", RED, assert->exp->out, NONE);
	}
	return (status);
}

static inline void	print_status_fail(t_assert *assert)
{
	char status_buffer[STATUS_BUFFER_SIZE];

	status_format(&assert->got->status, status_buffer, STATUS_BUFFER_SIZE);
	print_stderr("[%s%s%s] has [%s%s%s] ", RED, assert->got_name, NONE, RED, status_buffer, NONE);

	status_format(&assert->exp->status, status_buffer, STATUS_BUFFER_SIZE);
	print_stderr("instead of [%s%s%s]\n", RED, status_buffer, NONE);
}

static inline void	print_ret_fail(t_assert *assert)
{
	print_stderr("%s    %s %s FAILED%s:  [%s%s%s] ", RED, EMJ_ARW_DR, EMJ_FAIL, NONE, RED, assert->got_name, NONE);
	if (assert->format == F_STRUCT)
		print_stderr("%sreturned%s [%sunexpected struct content%s]\n", YELLOW, NONE, RED, NONE);
	else if (assert->format == F_STRING)
	{
		print_stderr("%sreturned%s [%s%s%s] ", YELLOW, NONE, RED, (char *)assert->got->ret, NONE);
		print_stderr("instead of [%s%s%s]\n", RED, (char *)assert->exp->ret, NONE);
	}
	else if (assert->format == F_CHAR)
	{
		print_stderr("%sreturned%s [%s%c%s] ", YELLOW, NONE, RED, (char)assert->got->ret, NONE);
		print_stderr("instead of [%s%c%s]\n", RED, (char)assert->exp->ret, NONE);
	}
	else if (assert->format == F_SIGNED)
	{
		print_stderr("%sreturned%s [%s%" PRIdPTR "%s] ", YELLOW, NONE, RED, (intptr_t)assert->got->ret, NONE);
		print_stderr("instead of [%s%" PRIdPTR "%s]\n", RED, (intptr_t)assert->exp->ret, NONE);
	}
	else if (assert->format == F_UNSIGNED)
	{
		print_stderr("%sreturned%s [%s%" PRIuPTR "%s] ", YELLOW, NONE, RED, (uintptr_t)assert->got->ret, NONE);
		print_stderr("instead of [%s%" PRIuPTR "%s]\n", RED, (uintptr_t)assert->exp->ret, NONE);
	}
	else
	{
		print_stderr("%sreturned%s [%s%" PRIxPTR "%s] ", YELLOW, NONE, RED, (uintptr_t)assert->got->ret, NONE);
		print_stderr("instead of [%s%" PRIxPTR "%s]\n", RED, (uintptr_t)assert->exp->ret, NONE);
	}
}
