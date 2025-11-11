#include "test.h"

void	test_p(void)
{
	printf(" %s⏱%s Testing %s'%%p'%s with %sstack address%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	int a = 42;
	int b = -1;
	iterate_on_pointer("%p", &a);
	iterate_on_pointer("%p", &b);

	printf(" %s⏱%s Testing %s'%%p'%s with %sheap address%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	void *ptr1 = malloc(1);
	void *ptr2 = malloc(1000);
	iterate_on_pointer("%p", ptr1);
	iterate_on_pointer("%p", ptr2);
	free(ptr1);
	free(ptr2);

	printf(" %s⏱%s Testing %s'%%p'%s with %sNULL pointer%s\n", BLUE, NONE, BLUE, NONE, BLUE, NONE);
	iterate_on_pointer("%p", NULL);

	printf("\n");
}
