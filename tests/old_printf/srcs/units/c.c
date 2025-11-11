#include "test.h"

void	test_c(void)
{
	printf(" %s⏱%s Testing %s'%%c'%s with %sprintable chars%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%c", 'A');
	iterate_on_long("%c", 'z');
	iterate_on_long("%c", 33);
	iterate_on_long("%c", 126);

	printf(" %s⏱%s Testing %s'%%c'%s with %snon-printable chars%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%c", '\0');
	iterate_on_long("%c", 7);
	iterate_on_long("%c", '\t');
	iterate_on_long("%c", 10);
	iterate_on_long("%c", '\v');
	iterate_on_long("%c", '\r');
	iterate_on_long("%c", 31);
	iterate_on_long("%c", 127);

	printf(" %s⏱%s Testing %s'%%c'%s with %ssigned values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%c", -1);
	iterate_on_long("%c", -42);
	iterate_on_long("%c", -128);

	printf(" %s⏱%s Testing %s'%%c'%s with %sunsigned overflow%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%c", 255);
	iterate_on_long("%c", 256);
	iterate_on_long("%c", 257);
	iterate_on_long("%c", 512);
	iterate_on_long("%c", 1024);

	printf(" %s⏱%s Testing %s'%%c'%s with %slimits%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_long("%c", INT_MAX);
	iterate_on_long("%c", INT_MIN);
	iterate_on_long("%c", UINT_MAX);

	printf("\n");
}
