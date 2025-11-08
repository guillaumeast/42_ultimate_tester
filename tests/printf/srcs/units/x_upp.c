#include "test.h"

void	test_x_upp(void)
{
	printf(" %s⏱%s Testing %s'%%X' with basic values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%X", 0);
	run_test_unsigned("%X", 42);

	printf(" %s⏱%s Testing %s'%%X' with padding and spacing%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("-%X-", 0);
	run_test_unsigned(" %X ", 42);

	printf(" %s⏱%s Testing %s'%%X' with int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%X", INT_MIN);
	run_test_unsigned("%X", INT_MAX);

	printf(" %s⏱%s Testing %s'%%X' with unsigned int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%X", UINT_MAX);

	printf(" %s⏱%s Testing %s'%%X' with negative values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%X", -1);
	run_test_long("%X", -42);

	printf("\n");
}
