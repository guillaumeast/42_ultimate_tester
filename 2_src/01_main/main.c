#define __FUT_INSIDE__
#include "report_priv.h"
#include "set_priv.h"
#undef __FUT_INSIDE__

#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor(102)))
static void	ult_main(void)
{
	t_set	*set;

	set = set_get_first();
	while (set)
	{
		set_run(set);
		set = set->next;
	}

	print_report(&g_result);

	exit(EXIT_SUCCESS);
}

__attribute__((weak))
int	main(void)
{
	return (0);
}
