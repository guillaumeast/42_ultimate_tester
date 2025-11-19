#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#include "assert_pub.h"
#include "compare_int.h"
#include "print_priv.h"
#undef __FUT_ENGINE_INSIDE__
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
	if (assert->mode != OUT && assert->mode != ERR && assert->mode != BOTH)
		ret_res = check_ret(assert);

	out_res.type = PASSED;
	if (assert->mode != RET)
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
	if (assert->got_capt->status.type != DONE || assert->exp_capt->status.type != DONE)
	{
		if (assert->got_capt->status.type == CRASHED)
		{
			status.type = CRASHED;
			status.sig = assert->got_capt->status.sig;
			print_stderr("%s  %s %sCRASHED %s%s%s ", RED, EMJ_ARW_DR, EMJ_CRSH_Y, GREY, EMJ_ARW_RIGHT, NONE);
			print_status_fail(assert->got_name, &assert->got_capt->status);
		}
		else if (assert->got_capt->status.type == TIMED)
		{
			status.type = TIMED;
			status.timeout = assert->got_capt->status.timeout;
			print_stderr("%s  %s %sTIMED   %s%s%s ", RED, EMJ_ARW_DR, EMJ_TIMD, GREY, EMJ_ARW_RIGHT, NONE);
			print_status_fail(assert->got_name, &assert->got_capt->status);
		}
		else if (assert->exp_capt->status.type == CRASHED)
		{
			status.type = CRASHED;
			status.sig = assert->exp_capt->status.sig;
			print_stderr("%s  %s %sCRASHED %s%s%s ", RED, EMJ_ARW_DR, EMJ_CRSH_Y, GREY, EMJ_ARW_RIGHT, NONE);
			print_status_fail(assert->exp_name, &assert->exp_capt->status);
		}
		else if (assert->exp_capt->status.type == TIMED)
		{
			status.type = TIMED;
			status.timeout = assert->exp_capt->status.timeout;
			print_stderr("%s  %s %sTIMED   %s%s%s ", RED, EMJ_ARW_DR, EMJ_TIMD, GREY, EMJ_ARW_RIGHT, NONE);
			print_status_fail(assert->exp_name, &assert->exp_capt->status);
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
		if (compare_strings((const char *)assert->got_capt->ret, (const char *)assert->exp_capt->ret))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (assert->format == F_STRUCT)
	{
		if (compare_structs((const void *)assert->got_capt->ret, (const void *)assert->exp_capt->ret, assert->ret_size))
		{
			status.type = FAILED;
			print_ret_fail(assert);
		}
	}
	else if (compare_intptr_t(assert->got_capt->ret, assert->exp_capt->ret))
	{
		status.type = FAILED;
		print_ret_fail(assert);
	}
	return (status);
}

static inline t_status	check_out(t_assert *assert)
{
	t_status	status = {0};

	if (!compare_strings(assert->got_capt->out, assert->exp_capt->out))
		status.type = PASSED;
	else
	{
		status.type = FAILED;
		print_stderr("%s  %s %sFAILED  %s%s%s %s ", RED, EMJ_ARW_DR, EMJ_FAIL, GREY, EMJ_ARW_RIGHT, RED, assert->got_name);
		print_raw_err("%soutputed%s '%s%s%s' ", YELLOW, GREY, RED, assert->got_capt->out, GREY);
		print_raw_err("instead of %sanything else%s\n", RED, NONE);
	}
	return (status);
}

static inline void	print_status_fail(const char *expr_name, t_status *status)
{
	char status_buffer[STATUS_BUFFER_SIZE];
	
	status_format(status, status_buffer, STATUS_BUFFER_SIZE);
	print_raw_err("%s%s%s has %s%s%s\n", RED, expr_name, GREY, YELLOW, status_buffer, NONE);
}

static inline void	print_ret_fail(t_assert *assert)
{
	print_stderr("%s  %s %sFAILED  %s%s%s %s ", RED, EMJ_ARW_DR, EMJ_FAIL, GREY, EMJ_ARW_RIGHT, RED, assert->got_name);
	if (assert->format == F_STRUCT)
	{
		print_raw_err("%sreturned%s %ssame struct content%s\n", YELLOW, GREY, RED, NONE);
		return ;
	}
	else if (assert->format == F_STRING)
		print_raw_err("%sreturned%s '%s%s%s' ", YELLOW, GREY, RED, (char *)assert->got_capt->ret, GREY);
	else if (assert->format == F_CHAR)
		print_raw_err("%sreturned%s %s%c%s ", YELLOW, NONE, RED, (char)assert->got_capt->ret, GREY);
	else if (assert->format == F_SIGNED)
		print_raw_err("%sreturned%s %s%" PRIdPTR "%s ", YELLOW, NONE, RED, (intptr_t)assert->got_capt->ret, GREY);
	else if (assert->format == F_UNSIGNED)
		print_raw_err("%sreturned%s %s%" PRIuPTR "%s ", YELLOW, NONE, RED, (uintptr_t)assert->got_capt->ret, GREY);
	else
		print_raw_err("%sreturned%s %s%" PRIxPTR "%s ", YELLOW, NONE, RED, (uintptr_t)assert->got_capt->ret, GREY);
	print_raw_err("instead of %sanything else%s\n", RED, NONE);
}
