#define __FUT_INSIDE__
#define __FUT_ENGINE_INSIDE__
#define __FUT_SET_INSIDE__
#include "print_wrapper_pub.h"
#include "set_internal.h"
#undef __FUT_SET_INSIDE__
#undef __FUT_ENGINE_INSIDE__
#undef __FUT_INSIDE__

#include <string.h>

t_result		g_result;
static size_t	s_h1_max_len;

void	set_run(t_set *set)
{
	logs_print_h1("%-*s ", (int)s_h1_max_len, set->name);
	set->result.status.type = RUNNING;

	_fork_init(set->timeout);
	if (g_context.child_pid > 0)
		set_run_parent(set);
	else
		set_run_child(set);

	if (set->result.status.type != PASSED)
		print_stdout("\n");
}

void	set_init(t_set *first_set, t_set *last_set)
{
	t_set	*set;
	size_t	len;

	for (set = first_set; set < last_set; set++)
	{
		len = strlen(set->name);
		if (len > s_h1_max_len)
			s_h1_max_len = len;
	}
}
