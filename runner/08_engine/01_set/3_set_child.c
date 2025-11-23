#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <stdlib.h>
#include <unistd.h>

void	set_run_child(t_set *set)
{
	set->func();

	fork_cleanup(&s_context);
	exit(EXIT_SUCCESS);
}
