#include "test.h"

void	test_p(void)
{
	printf(" %s⏱%s Testing %s'%%p' with NULL pointer%s\n", BLUE, NONE, BLUE, NONE);
	run_test_pointer("%p", NULL);

	printf(" %s⏱%s Testing %s'%%p' with stack address\n");
	int a = 42;
	int b = -1;
	run_test_pointer("%p", &a);
	run_test_pointer("%p", &b);
	run_test_pointer("-%p-", &a);
	run_test_pointer(" %p ", &b);

	printf(" %s⏱%s Testing %s'%%p' with heap address\n");
	void *ptr1 = malloc(1);
	void *ptr2 = malloc(1000);
	run_test_pointer("%p", ptr1);
	run_test_pointer("%p", ptr2);
	run_test_pointer("-%p-", ptr1);
	run_test_pointer(" %p ", ptr2);
	free(ptr1);
	free(ptr2);

	printf(" %s⏱%s Testing %s'%%p' with int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_pointer("%p", (void *)INT_MIN);
	run_test_pointer("%p", (void *)INT_MAX);

	printf(" %s⏱%s Testing %s'%%p' with unisgned int limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_pointer("%p", (void *)UINT_MAX);

	printf(" %s⏱%s Testing %s'%%p' with long limits%s\n", BLUE, NONE, BLUE, NONE);
	run_test_pointer("%p", (void *)LONG_MIN);
	run_test_pointer("%p", (void *)LONG_MAX);

	printf("\n");
}
