#include "test.h"

void	test_d(void)
{
	printf(" %s⏱%s Testing %s'%%d'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%d", 0);
	iterate_on_long("%d", 1);

	printf(" %s⏱%s Testing %s'%%d'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%d", +0);
	iterate_on_long("%d", -0);
	iterate_on_long("%d", +1);
	iterate_on_long("%d", -1);

	printf(" %s⏱%s Testing %s'%%d'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%d", INT_MAX);
	iterate_on_long("%d", INT_MIN);

	printf("\n");
}
