#include "test.h"

void	test_s(void)
{
	printf(" %s⏱%s Testing %s'%%s'%s with %sbasic values%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_string("%s", "Hello");
	run_test_string("%s", "world");
	run_test_string("%s", "");
	run_test_string("%s", " ");
	run_test_string("%s", "42");
	run_test_string("%s", "Hello World");

	printf(" %s⏱%s Testing %s'%%s'%s with %sspecial characters%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_string("%s", "\tTab\tSeparated");
	run_test_string("%s", "\nNew\nLine");
	run_test_string("%s", "\rCarriage\r 💥\033[0;31m Timeout or Crash: ft_printf(\"%%s\", \"\\rCarriage\\rReturn\\\"\033[0;0m");
	run_test_string("%s", "abc\0def");

	printf(" %s⏱%s Testing %s'%%s'%s with %sNULL pointer%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	run_test_string("%s", NULL);

	printf("\n");
}
