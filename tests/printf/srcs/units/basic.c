#include "test.h"

void	test_basic(void)
{
	printf(" %s⏱%s Testing %sempty string%s\n", BLUE, NONE, BLUE, NONE);
	iterate_no_arg("");

	printf(" %s⏱%s Testing %sconversion-less strings%s\n", BLUE, NONE, BLUE, NONE);
	iterate_no_arg("a");
	iterate_no_arg("\t");
	iterate_no_arg("\n");
	iterate_no_arg("Hello World");
	iterate_no_arg("\033[0;34mColored\033[0;34mstring\033[0;0m");
	
	printf("\n %s⏱%s Testing %s'%%%%'%s\n", BLUE, NONE, BLUE, NONE);
	iterate_on_long("%%", 0);

	printf("\n");
}
