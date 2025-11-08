#include "test.h"

void	test_u(void)
{
	printf(" %s⏱%s Testing %s'%%u'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_unsigned("%u", 0);
	run_test_unsigned("%u", 1);
	run_test_unsigned("%u", 42);

	printf(" %s⏱%s Testing %s'%%u'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_long("%u", -1);
	run_test_long("%u", -42);
	run_test_unsigned("%u", INT_MIN);
	run_test_unsigned("%u", INT_MAX);
	run_test_unsigned("%u", UINT_MAX);

	printf("\n");
}
