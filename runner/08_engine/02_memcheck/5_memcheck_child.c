#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "memcheck_int.h"
#include "process_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	_memcheck_child(const char *expr, t_context *ctx)
{
	t_result	result = {0};

	memcheck_disable();

	for (size_t i = 0; i < g_leaks_count; i++)
	{
		send_leak(ctx, expr, g_leaks_table[i].size, g_leaks_table[i].caller);
		result.leaks++;
	}

	result_compute(&result);
	message_send(ctx->pipe, RESULT, (t_message_data *)&result);

	fork_cleanup(ctx);

	exit(EXIT_SUCCESS);
}
