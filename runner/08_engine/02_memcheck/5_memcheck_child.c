#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "memcheck_int.h"
#include "messages_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>

void	_memcheck_child(const char *expr)
{
	t_result	result = {0};

	memcheck_disable();

	for (size_t i = 0; i < g_leaks_count; i++)
	{
		send_leak(expr, g_leaks_table[i].size, g_leaks_table[i].caller);
		result.leaks++;
	}

	result_compute(&result);
	message_send(g_context.pipe_to_parent, RESULT, (t_message_data *)&result);

	fork_cleanup();

	exit(EXIT_SUCCESS);
}
