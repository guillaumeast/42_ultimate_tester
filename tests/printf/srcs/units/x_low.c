#include "test.h"

void	test_x_low(void)
{
	printf(" %s⏱%s Testing %s'%%x'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_unsigned("%x", 0);
	iterate_on_unsigned("%x", 42);

	printf(" %s⏱%s Testing %s'%%x'%s with %snegative values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%x", -1);
	iterate_on_long("%x", -42);

	printf(" %s⏱%s Testing %s'%%x'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%x", INT_MIN);
	iterate_on_unsigned("%x", INT_MAX);
	iterate_on_unsigned("%x", UINT_MAX);

	printf("\n");
}
