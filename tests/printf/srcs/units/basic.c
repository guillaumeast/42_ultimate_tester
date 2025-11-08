#include "test.h"

void	test_basic(void)
{
	printf(" %s⏱%s Testing %sempty string%s\n", BLUE, NONE, BLUE, NONE);
	run_test_no_arg("");
	run_test_string("", "Hello World");

	printf(" %s⏱%s Testing %sconversion-less strings%s\n", BLUE, NONE, BLUE, NONE);
	run_test_no_arg("a");
	run_test_no_arg("Hello World");
	run_test_no_arg("\tHello\tWorld\t");
	run_test_no_arg("\033[0;34mColored\033[0;34mstring\033[0;0m");

	printf(" %s⏱%s Testing %sincorrect arguments count%s\n", BLUE, NONE, BLUE, NONE);
	run_test_no_arg("Too few arguments");
	run_test_string("Too many arguments", "This argument should not be ");

	printf(" %s⏱%s Testing %s'%%%%'%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("%%", 0);
	run_test_long(" %% ", 0);
	run_test_long("-%%-", 0);

	printf(" %s⏱%s Testing %s'%%_' (invalid format)%s\n", BLUE, NONE, BLUE, NONE);
	run_test_long("12%_45", 0);

	printf("\n");
}
