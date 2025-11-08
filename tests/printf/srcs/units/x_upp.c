#include "test.h"

void	test_x_upp(void)
{
	printf(" %s⏱%s Testing %s'%%X'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_unsigned("%X", 0);
	iterate_on_unsigned("%X", 42);

	printf(" %s⏱%s Testing %s'%%X'%s with %snegative values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%X", -1);
	iterate_on_long("%X", -42);

	printf(" %s⏱%s Testing %s'%%X'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%X", INT_MIN);
	iterate_on_unsigned("%X", INT_MAX);
	iterate_on_unsigned("%X", UINT_MAX);

	printf("\n");
}
