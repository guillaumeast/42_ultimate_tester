#include "test.h"

void	test_p(void)
{
	printf(" ⏱ Testing '%%p' with NULL pointer\n");
	run_test_pointer("%p", NULL);

	printf(" ⏱ Testing '%%p' with stack address\n");
	int a = 42;
	int b = -1;
	run_test_pointer("%p", &a);
	run_test_pointer("%p", &b);
	run_test_pointer("-%p-", &a);
	run_test_pointer(" %p ", &b);

	printf(" ⏱ Testing '%%p' with heap address\n");
	void *ptr1 = malloc(1);
	void *ptr2 = malloc(1000);
	run_test_pointer("%p", ptr1);
	run_test_pointer("%p", ptr2);
	run_test_pointer("-%p-", ptr1);
	run_test_pointer(" %p ", ptr2);
	free(ptr1);
	free(ptr2);

	printf(" ⏱ Testing '%%p' with int limits\n");
	run_test_pointer("%p", (void *)INT_MIN);
	run_test_pointer("%p", (void *)INT_MAX);

	printf(" ⏱ Testing '%%p' with unisgned int limits\n");
	run_test_pointer("%p", (void *)UINT_MAX);

	printf(" ⏱ Testing '%%p' with long limits\n");
	run_test_pointer("%p", (void *)LONG_MIN);
	run_test_pointer("%p", (void *)LONG_MAX);

	printf("\n");
}
