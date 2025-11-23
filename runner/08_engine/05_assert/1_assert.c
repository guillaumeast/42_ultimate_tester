#define __FUT_INSIDE__
#define __FUT_ASSERT_INSIDE__
#include "assert_int.h"
#include "messages_priv.h"
#undef __FUT_ASSERT_INSIDE__
#undef __FUT_INSIDE__

void	_assert_run(t_assert *assert)
{
	t_status	status = {0};
	t_result	result = {0};

	if (assert->eq == true)
		status = assert_check_eq(assert);
	else
	 	status = assert_check_neq(assert);

	if (status.type == PASSED)
		result.passed++;
	else if (status.type == FAILED)
		result.failed++;
	else if (status.type == TIMED)
		result.timed++;
	else if (status.type == CRASHED)
		result.crashed++;

	result_compute(&result);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);
}
