#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#include "assert_pub.h"
#include "compare_engine.h"
#include "send_priv.h"
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <inttypes.h>

static inline t_status	check_status(t_assert *assert);
static inline bool		check_ret(t_assert *assert);
static inline bool		check_out(t_assert *assert);

t_status	assert_check_eq(t_assert *assert)
{
	t_status	status_res = {0};
	bool		ret_passed;
	bool		out_passed;
	t_status	final_res = {0};
	
	status_res = check_status(assert);
	if (status_res.type != PASSED)
		return (status_res);

	if (assert->mode != OUT && assert->mode != ERR && assert->mode != BOTH)
		ret_passed = check_ret(assert);

	if (assert->mode != RET)
		out_passed = check_out(assert);

	if (ret_passed && out_passed)
		final_res.type = PASSED;
	else
		final_res.type = FAILED;
	
	return (final_res);
}

static inline t_status	check_status(t_assert *assert)
{
	t_status	status = {0};

	if (compare_status(&assert->got_capt->status, &assert->exp_capt->status))
		status.type = PASSED;
	else if (assert->got_capt->status.type == CRASHED)
	{
		status.type = CRASHED;
		send_incorrect_status(assert->got_name, &assert->got_capt->status, &assert->exp_capt->status);
	}
	else if (assert->got_capt->status.type == TIMED)
	{
		status.type = TIMED;
		send_incorrect_status(assert->got_name, &assert->got_capt->status, &assert->exp_capt->status);
	}
	else
	{
		status.type = FAILED;
		send_incorrect_status(assert->got_name, &assert->got_capt->status, &assert->exp_capt->status);
	}
	return (status);
}

static inline bool	check_ret(t_assert *a)
{
	if (a->format == F_STRING && !compare_strings((const char *)a->got_capt->ret, (const char *)a->exp_capt->ret))
	{
		send_incorrect_return(a->got_name, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	else if (a->format == F_STRUCT && !compare_structs((const void *)a->got_capt->ret, (const void *)a->exp_capt->ret, a->ret_size))
	{
		send_incorrect_return(a->got_name, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	else if (!compare_intptr_t(a->got_capt->ret, a->exp_capt->ret))
	{
		send_incorrect_return(a->got_name, a->format, a->got_capt->ret, &a->exp_capt->ret);
		return (false);
	}
	return (true);
}

static inline bool	check_out(t_assert *assert)
{
	if (!compare_strings(assert->got_capt->out, assert->exp_capt->out))
	{
		send_incorrect_output(assert->got_name, assert->got_capt->out, assert->exp_capt->out);
		return (false);
	}
	return (true);
}


