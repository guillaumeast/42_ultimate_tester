#include "test.h"

void	test_s(void)
{
	printf(" %s⏱%s Testing %s'%%s' with basic values%s\n", BLUE, NONE, BLUE, NONE);
	run_test_string("%s", "Hello");
	run_test_string("%s", "world");
	run_test_string("%s", "");
	run_test_string("%s", " ");
	run_test_string("%s", "42");
	run_test_string("%s", "Hello World");

	printf(" %s⏱%s Testing %s'%%s' with basic special characters%s\n", BLUE, NONE, BLUE, NONE);
	run_test_string("%s", "\tTab\tSeparated");
	run_test_string("%s", "\nNew\nLine");
	run_test_string("%s", "\rCarriage\rReturn");
	run_test_string("%s", "Mix: \t\n\r");
	run_test_string("%s", "abc\0def");

	printf(" %s⏱%s Testing %s'%%s' with NULL pointer%s\n", BLUE, NONE, BLUE, NONE);
	run_test_string("%s", NULL);

	printf("\n");
}
