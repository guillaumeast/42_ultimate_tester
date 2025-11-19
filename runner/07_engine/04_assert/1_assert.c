#define __FUT_INSIDE__
#define __FUT_ASSERT_INSIDE__
#include "assert_int.h"
#include "set_priv.h"
#include "result_pub.h"
#undef __FUT_ASSERT_INSIDE__
#undef __FUT_INSIDE__

/*
**	TODO:
**	1. Check & build t_result
**	2. Print logs (only if != PASSED)
*/
void	_fut_assert_run(t_assert *assert)
{
	t_status	status = {0};
	t_result	result = {0};

	if (assert->eq == true)
		status = check_assert_eq(assert);
	else
	 	status = check_assert_neq(assert);

	if (status.type == PASSED)
		result.passed++;
	else if (status.type == FAILED)
		result.failed++;
	else if (status.type == TIMED)
		result.timed++;
	else if (status.type == CRASHED)
		result.crashed++;
	result.total++;
	set_add_result(&result);
}
