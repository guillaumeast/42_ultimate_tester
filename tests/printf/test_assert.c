#include "ft_ultimate_tester.h"
#include "libftprintf.h"
#include <stdlib.h>

#include <inttypes.h>

Test(eq_pass, 0)
{
	assert_eq(GET_RET_OUT, 1, (printf("%i", -42)), (ft_printf("%i", 42)));
	assert_neq(GET_RET_OUT, 1, (printf("%i", -42)), (ft_printf("%i", -42)));
}
// assert_eq(GET_RET, 1, (printf("%c", 'a')), (ft_printf("%c", 'a')));

	// assert_eq("assert_eq(expl char)", (char)'a', (char)'a');
	// assert_eq("assert_eq(expl signed char)", (signed char)'a', (signed char)'a');
	// assert_eq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

	// assert_eq("assert_eq(expl short)", (short)-42, (short)-42);
	// assert_eq("assert_eq(expl signed short)", (signed short)-42, (signed short)-42);
	// assert_eq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

	// assert_eq("assert_eq(impl bool)", true, true);
	// assert_eq("assert_eq(expl bool)", (bool)true, (bool)true);

	// assert_eq("assert_eq(impl int)", -42, -42);
	// assert_eq("assert_eq(expl int)", (int)-42, (int)-42);
	// assert_eq("assert_eq(expl signed int)", (signed int)-42, (signed int)-42);
	// assert_eq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

	// assert_eq("assert_eq(expl long)", (long)-42, (long)-42);
	// assert_eq("assert_eq(expl signed long)", (signed long)-42, (signed long)-42);
	// assert_eq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

	// assert_eq("assert_eq(expl long long)", (long long)-42, (long long)-42);
	// assert_eq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
	// assert_eq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

	// assert_eq("assert_eq(expl size_t)", (size_t)42, (size_t)42);

	// assert_eq("assert_eq(impl NULL *)", NULL, NULL);
	// assert_eq("assert_eq(expl NULL *)", (void *)NULL, (void *)NULL);

	// int stack = 0;
	// assert_eq("assert_eq(impl stack *)", &stack, &stack);
	// assert_eq("assert_eq(expl stack int *)", (int *)&stack, (int *)&stack);
	// assert_eq("assert_eq(expl stack void *)", (void *)&stack, (void *)&stack);

	// int *heap;
	// heap = malloc(sizeof(int));
	// assert_eq("assert_eq(impl heap *)", &heap, &heap);
	// assert_eq("assert_eq(expl heap int *)", (int *)&heap, (int *)&heap);
	// assert_eq("assert_eq(expl heap void *)", (void *)&heap, (void *)&heap);
	// free (heap);

	// assert_eq("assert_eq(impl char *)", "42", "42");
	// assert_eq("assert_eq(expl char *)", (char *)"42", (char *)"42");
	// assert_eq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
	// assert_eq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
// }

// Test(eq_fail, 0)
// {
// 	assert_eq("assert_eq(impl char)", 'a', 'b');
// 	assert_eq("assert_eq(expl char)", (char)'a', (char)'b');
// 	assert_eq("assert_eq(expl signed char)", (signed char)'a', (signed char)'b');
// 	assert_eq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

// 	assert_eq("assert_eq(expl short)", (short)-42, (short)-1);
// 	assert_eq("assert_eq(expl signed short)", (signed short)-42, (signed short)-1);
// 	assert_eq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

// 	assert_eq("assert_eq(impl bool)", true, false);
// 	assert_eq("assert_eq(expl bool)", (bool)true, (bool)false);

// 	assert_eq("assert_eq(impl int)", -42, -1);
// 	assert_eq("assert_eq(expl int)", (int)-42, (int)-1);
// 	assert_eq("assert_eq(expl signed int)", (signed int)-42, (signed int)-1);
// 	assert_eq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

// 	assert_eq("assert_eq(expl long)", (long)-42, (long)-1);
// 	assert_eq("assert_eq(expl signed long)", (signed long)-42, (signed long)-1);
// 	assert_eq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

// 	assert_eq("assert_eq(expl long long)", (long long)-42, (long long)-1);
// 	assert_eq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
// 	assert_eq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

// 	assert_eq("assert_eq(expl size_t)", (size_t)42, (size_t)1);

// 	int stack = 0;
// 	assert_eq("assert_eq(impl stack *)", &stack, NULL);
// 	assert_eq("assert_eq(expl stack int *)", (int *)&stack, (int *)NULL);
// 	assert_eq("assert_eq(expl stack void *)", (void *)&stack, (void *)NULL);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_eq("assert_eq(impl heap *)", &heap, NULL);
// 	assert_eq("assert_eq(expl heap int *)", (int *)&heap, (int *)NULL);
// 	assert_eq("assert_eq(expl heap void *)", (void *)&heap, (void *)NULL);
// 	free (heap);

// 	assert_eq("assert_eq(impl char *)", "42", "1");
// 	assert_eq("assert_eq(expl char *)", (char *)"42", (char *)"1");
// 	assert_eq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
// 	assert_eq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
// }

// Test(neq_fail, 0)
// {
// 	assert_neq("assert_eq(impl char)", 'a', 'a');
// 	assert_neq("assert_eq(expl char)", (char)'a', (char)'a');
// 	assert_neq("assert_eq(expl signed char)", (signed char)'a', (signed char)'a');
// 	assert_neq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

// 	assert_neq("assert_eq(expl short)", (short)-42, (short)-42);
// 	assert_neq("assert_eq(expl signed short)", (signed short)-42, (signed short)-42);
// 	assert_neq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

// 	assert_neq("assert_eq(impl bool)", true, true);
// 	assert_neq("assert_eq(expl bool)", (bool)true, (bool)true);

// 	assert_neq("assert_eq(impl int)", -42, -42);
// 	assert_neq("assert_eq(expl int)", (int)-42, (int)-42);
// 	assert_neq("assert_eq(expl signed int)", (signed int)-42, (signed int)-42);
// 	assert_neq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

// 	assert_neq("assert_eq(expl long)", (long)-42, (long)-42);
// 	assert_neq("assert_eq(expl signed long)", (signed long)-42, (signed long)-42);
// 	assert_neq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

// 	assert_neq("assert_eq(expl long long)", (long long)-42, (long long)-42);
// 	assert_neq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
// 	assert_neq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

// 	assert_neq("assert_eq(expl size_t)", (size_t)42, (size_t)42);

// 	assert_neq("assert_eq(impl NULL *)", NULL, NULL);
// 	assert_neq("assert_eq(expl NULL *)", (void *)NULL, (void *)NULL);

// 	int stack = 0;
// 	assert_neq("assert_eq(impl stack *)", &stack, &stack);
// 	assert_neq("assert_eq(expl stack int *)", (int *)&stack, (int *)&stack);
// 	assert_neq("assert_eq(expl stack void *)", (void *)&stack, (void *)&stack);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_neq("assert_eq(impl heap *)", &heap, &heap);
// 	assert_neq("assert_eq(expl heap int *)", (int *)&heap, (int *)&heap);
// 	assert_neq("assert_eq(expl heap void *)", (void *)&heap, (void *)&heap);
// 	free (heap);

// 	assert_neq("assert_eq(impl char *)", "42", "42");
// 	assert_neq("assert_eq(expl char *)", (char *)"42", (char *)"42");
// 	assert_neq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
// 	assert_neq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
// }

// Test(neq_pass, 0)
// {
// 	assert_neq("assert_eq(impl char)", 'a', 'b');
// 	assert_neq("assert_eq(expl char)", (char)'a', (char)'b');
// 	assert_neq("assert_eq(expl signed char)", (signed char)'a', (signed char)'b');
// 	assert_neq("assert_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

// 	assert_neq("assert_eq(expl short)", (short)-42, (short)-1);
// 	assert_neq("assert_eq(expl signed short)", (signed short)-42, (signed short)-1);
// 	assert_neq("assert_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

// 	assert_neq("assert_eq(impl bool)", true, false);
// 	assert_neq("assert_eq(expl bool)", (bool)true, (bool)false);

// 	assert_neq("assert_eq(impl int)", -42, -1);
// 	assert_neq("assert_eq(expl int)", (int)-42, (int)-1);
// 	assert_neq("assert_eq(expl signed int)", (signed int)-42, (signed int)-1);
// 	assert_neq("assert_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

// 	assert_neq("assert_eq(expl long)", (long)-42, (long)-1);
// 	assert_neq("assert_eq(expl signed long)", (signed long)-42, (signed long)-1);
// 	assert_neq("assert_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

// 	assert_neq("assert_eq(expl long long)", (long long)-42, (long long)-1);
// 	assert_neq("assert_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
// 	assert_neq("assert_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

// 	assert_neq("assert_eq(expl size_t)", (size_t)42, (size_t)1);

// 	int stack = 0;
// 	assert_neq("assert_eq(impl stack *)", &stack, NULL);
// 	assert_neq("assert_eq(expl stack int *)", (int *)&stack, (int *)NULL);
// 	assert_neq("assert_eq(expl stack void *)", (void *)&stack, (void *)NULL);

// 	int *heap;
// 	heap = malloc(sizeof(int));
// 	assert_neq("assert_eq(impl heap *)", &heap, NULL);
// 	assert_neq("assert_eq(expl heap int *)", (int *)&heap, (int *)NULL);
// 	assert_neq("assert_eq(expl heap void *)", (void *)&heap, (void *)NULL);
// 	free (heap);

// 	assert_neq("assert_eq(impl char *)", "42", "1");
// 	assert_neq("assert_eq(expl char *)", (char *)"42", (char *)"1");
// 	assert_neq("assert_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
// 	assert_neq("assert_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
// }

// Test(time_out, 1)
// {
// 	int	i = 0;

// 	(void)i;
// 	while (true)
// 		i++;
// }

// Test(crash, 0)
// {
// 	volatile int *oops;

// 	oops = NULL;
// 	*oops = 42;
// }
