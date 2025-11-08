#include "test.h"

void	test_s(void)
{
	printf(" %s⏱%s Testing %s'%%s'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_string("%s", "Hello");
	iterate_on_string("%s", "");
	iterate_on_string("%s", " ");
	iterate_on_string("%s", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

	printf(" %s⏱%s Testing %s'%%s'%s with %sspecial characters%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_string("%s", "\tTab\tSeparated");
	iterate_on_string("%s", "\nNew\nLine");
	iterate_on_string("%s", "Trunc\0ated");
	iterate_on_string("%s", "\033[0;34mColored\033[0;34m string\033[0;0m");

	printf(" %s⏱%s Testing %s'%%s'%s with %sNULL pointer%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_string("%s", NULL);
	iterate_on_string(" %s ", NULL);
	iterate_on_string("\t%s\t", NULL);
	iterate_on_string("%s", (char *)(uintptr_t)0);

	printf("\n");
}
