#include "test.h"

void	test_i(void)
{
	printf(" %s⏱%s Testing %s'%%i'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%i", 0);
	run_test_long("%i", 1);

	printf(" %s⏱%s Testing %s'%%i'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%i", +0);
	run_test_long("%i", -0);
	run_test_long("%i", +1);
	run_test_long("%i", -1);

	printf(" %s⏱%s Testing %s'%%i'%s with %sint limits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%i", INT_MAX);
	run_test_long("%i", INT_MIN);

	printf("\n");
}
