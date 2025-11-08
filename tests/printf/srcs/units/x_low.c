#include "test.h"

void	test_x_low(void)
{
	printf(" %s⏱%s Testing %s'%%x' with basic values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%x", 0);
	run_test_unsigned("%x", 42);

	printf(" %s⏱%s Testing %s'%%x' with padding and spacing%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("-%x-", 0);
	run_test_unsigned(" %x ", 42);

	printf(" %s⏱%s Testing %s'%%x' with int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%x", INT_MIN);
	run_test_unsigned("%x", INT_MAX);

	printf(" %s⏱%s Testing %s'%%x' with unsigned int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%x", UINT_MAX);

	printf(" %s⏱%s Testing %s'%%x' with negative values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%x", -1);
	run_test_long("%x", -42);

	printf("\n");
}
