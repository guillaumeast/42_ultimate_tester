#include "test.h"

void	test_x_upp(void)
{
	printf(" %s⏱%s Testing %s'%%X'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%X", 0);
	run_test_unsigned("%X", 42);

	printf(" %s⏱%s Testing %s'%%X'%s with %spadding and spacing%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_unsigned("-%X-", 0);
	run_test_unsigned(" %X ", 42);

	printf(" %s⏱%s Testing %s'%%X'%s with %sint limits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%X", INT_MIN);
	run_test_unsigned("%X", INT_MAX);

	printf(" %s⏱%s Testing %s'%%X'%s with %sunsigned int limits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%X", UINT_MAX);

	printf(" %s⏱%s Testing %s'%%X'%s with %snegative values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%X", -1);
	run_test_long("%X", -42);

	printf("\n");
}
