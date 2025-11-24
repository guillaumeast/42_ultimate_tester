#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "print_wrapper_pub.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

t_result	g_result;

void	set_run(t_set *set)
{
	logs_print_h1("%s", set->name);
	set->result.status.type = RUNNING;

	_fork_init(set->timeout);
	if (g_context.child_pid > 0)
		set_run_parent(set);
	else
		set_run_child(set);

	print_stderr("\n");
}
