#include "test.h"

void	test_basic(void)
{
	printf(" %s⏱%s Testing %s'%%%%'%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%%", 0);
	run_test_long(" %% ", 0);
	run_test_long("-%%-", 0);

	printf(" %s⏱%s Testing %s'%%_' (invalid format)%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("12%_45", 0);

	printf("\n");
}
