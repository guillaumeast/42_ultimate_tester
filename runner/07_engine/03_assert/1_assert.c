#define __FUT_INSIDE__
#define __FUT_ASSERT_INSIDE__
#include "assert_int.h"
#undef __FUT_ASSERT_INSIDE__
#undef __FUT_INSIDE__

/*
**	TODO:
**	1. Check & build t_result
**	2. Print logs (only if != PASSED)
*/
void	_fut_assert_run(t_assert *assert)
{
	t_status	status;

	if (assert->eq == true)
		status = check_assert_eq(assert);
	else
	 	status = check_assert_neq(assert);
	// TODO: send status to set module for update
}
