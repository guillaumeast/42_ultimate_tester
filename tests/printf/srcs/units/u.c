#include "test.h"

void	test_u(void)
{
	printf(" %s⏱%s Testing %s'%%u'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_unsigned("%u", 0);
	iterate_on_unsigned("%u", 42);

	printf(" %s⏱%s Testing %s'%%u'%s with %snegative values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%u", -1);
	iterate_on_long("%u", -42);

	printf(" %s⏱%s Testing %s'%%u'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_unsigned("%u", INT_MIN);
	iterate_on_unsigned("%u", INT_MAX);
	iterate_on_unsigned("%u", UINT_MAX);

	printf("\n");
}
