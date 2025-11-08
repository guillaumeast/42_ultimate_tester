#include "test.h"

void	test_d(void)
{
	printf(" %s⏱%s Testing %s'%%d'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%d", 0);
	run_test_long("%d", 1);

	printf(" %s⏱%s Testing %s'%%d'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%d", +0);
	run_test_long("%d", -0);
	run_test_long("%d", +1);
	run_test_long("%d", -1);

	printf(" %s⏱%s Testing %s'%%d'%s with %sint limits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%d", INT_MAX);
	run_test_long("%d", INT_MIN);

	printf("\n");
}
