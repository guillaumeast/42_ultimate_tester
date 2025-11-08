#include "test.h"

void	test_i(void)
{
	printf(" %s⏱%s Testing %s'%%i'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%i", 0);
	iterate_on_long("%i", 1);

	printf(" %s⏱%s Testing %s'%%i'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%i", +0);
	iterate_on_long("%i", -0);
	iterate_on_long("%i", +1);
	iterate_on_long("%i", -1);

	printf(" %s⏱%s Testing %s'%%i'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%i", INT_MAX);
	iterate_on_long("%i", INT_MIN);

	printf("\n");
}
