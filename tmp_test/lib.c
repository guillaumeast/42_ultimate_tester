#include "lib.h"
#include <stdio.h>

void	set_register(t_set *set)
{
	printf("Constructor called for set '%s'\n", set->name);
}

__attribute__((constructor(102)))
static void	ult_main(void)
{
	return;
}

__attribute__((weak))
int	main(void)
{
	return (0);
}
