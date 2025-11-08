#include "test.h"

void	test_i(void)
{
	printf(" %s⏱%s Testing %s'%%i' with basic values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%i", 0);
	run_test_long("%i", 1);

	printf(" %s⏱%s Testing %s'%%i' with signed values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%i", +0);
	run_test_long("%i", -0);
	run_test_long("%i", +1);
	run_test_long("%i", -1);

	printf(" %s⏱%s Testing %s'%%i' with int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%i", INT_MAX);
	run_test_long("%i", INT_MIN);

	printf("\n");
}
