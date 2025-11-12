#include "ft_ultimate_tester.h"
#include "libftprintf.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: explore this:
// #define macro_1(fn) typeof(fn)
// #define macro_2(fn) typeof(&fn)

Test(eq_pass, 0)
{
	expect_eq("expect_eq(impl char)", 'a', 'a');
	expect_eq("expect_eq(expl char)", (char)'a', (char)'a');
	expect_eq("expect_eq(expl signed char)", (signed char)'a', (signed char)'a');
	expect_eq("expect_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

	expect_eq("expect_eq(expl short)", (short)-42, (short)-42);
	expect_eq("expect_eq(expl signed short)", (signed short)-42, (signed short)-42);
	expect_eq("expect_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

	expect_eq("expect_eq(impl bool)", true, true);
	expect_eq("expect_eq(expl bool)", (bool)true, (bool)true);

	expect_eq("expect_eq(impl int)", -42, -42);
	expect_eq("expect_eq(expl int)", (int)-42, (int)-42);
	expect_eq("expect_eq(expl signed int)", (signed int)-42, (signed int)-42);
	expect_eq("expect_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

	expect_eq("expect_eq(expl long)", (long)-42, (long)-42);
	expect_eq("expect_eq(expl signed long)", (signed long)-42, (signed long)-42);
	expect_eq("expect_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

	expect_eq("expect_eq(expl long long)", (long long)-42, (long long)-42);
	expect_eq("expect_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
	expect_eq("expect_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

	expect_eq("expect_eq(expl size_t)", (size_t)42, (size_t)42);

	expect_eq("expect_eq(impl NULL *)", NULL, NULL);
	expect_eq("expect_eq(expl NULL *)", (void *)NULL, (void *)NULL);

	int stack = 0;
	expect_eq("expect_eq(impl stack *)", &stack, &stack);
	expect_eq("expect_eq(expl stack int *)", (int *)&stack, (int *)&stack);
	expect_eq("expect_eq(expl stack void *)", (void *)&stack, (void *)&stack);

	int *heap;
	heap = malloc(sizeof(int));
	expect_eq("expect_eq(impl heap *)", &heap, &heap);
	expect_eq("expect_eq(expl heap int *)", (int *)&heap, (int *)&heap);
	expect_eq("expect_eq(expl heap void *)", (void *)&heap, (void *)&heap);
	free (heap);

	expect_eq("expect_eq(impl char *)", "42", "42");
	expect_eq("expect_eq(expl char *)", (char *)"42", (char *)"42");
	expect_eq("expect_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
	expect_eq("expect_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
}

Test(eq_fail, 0)
{
	expect_eq("expect_eq(impl char)", 'a', 'b');
	expect_eq("expect_eq(expl char)", (char)'a', (char)'b');
	expect_eq("expect_eq(expl signed char)", (signed char)'a', (signed char)'b');
	expect_eq("expect_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

	expect_eq("expect_eq(expl short)", (short)-42, (short)-1);
	expect_eq("expect_eq(expl signed short)", (signed short)-42, (signed short)-1);
	expect_eq("expect_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

	expect_eq("expect_eq(impl bool)", true, false);
	expect_eq("expect_eq(expl bool)", (bool)true, (bool)false);

	expect_eq("expect_eq(impl int)", -42, -1);
	expect_eq("expect_eq(expl int)", (int)-42, (int)-1);
	expect_eq("expect_eq(expl signed int)", (signed int)-42, (signed int)-1);
	expect_eq("expect_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

	expect_eq("expect_eq(expl long)", (long)-42, (long)-1);
	expect_eq("expect_eq(expl signed long)", (signed long)-42, (signed long)-1);
	expect_eq("expect_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

	expect_eq("expect_eq(expl long long)", (long long)-42, (long long)-1);
	expect_eq("expect_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
	expect_eq("expect_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

	expect_eq("expect_eq(expl size_t)", (size_t)42, (size_t)1);

	int stack = 0;
	expect_eq("expect_eq(impl stack *)", &stack, NULL);
	expect_eq("expect_eq(expl stack int *)", (int *)&stack, (int *)NULL);
	expect_eq("expect_eq(expl stack void *)", (void *)&stack, (void *)NULL);

	int *heap;
	heap = malloc(sizeof(int));
	expect_eq("expect_eq(impl heap *)", &heap, NULL);
	expect_eq("expect_eq(expl heap int *)", (int *)&heap, (int *)NULL);
	expect_eq("expect_eq(expl heap void *)", (void *)&heap, (void *)NULL);
	free (heap);

	expect_eq("expect_eq(impl char *)", "42", "1");
	expect_eq("expect_eq(expl char *)", (char *)"42", (char *)"1");
	expect_eq("expect_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
	expect_eq("expect_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
}

Test(neq_fail, 0)
{
	expect_neq("expect_eq(impl char)", 'a', 'a');
	expect_neq("expect_eq(expl char)", (char)'a', (char)'a');
	expect_neq("expect_eq(expl signed char)", (signed char)'a', (signed char)'a');
	expect_neq("expect_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'a');

	expect_neq("expect_eq(expl short)", (short)-42, (short)-42);
	expect_neq("expect_eq(expl signed short)", (signed short)-42, (signed short)-42);
	expect_neq("expect_eq(expl unsigned short)", (unsigned short)42, (unsigned short)42);

	expect_neq("expect_eq(impl bool)", true, true);
	expect_neq("expect_eq(expl bool)", (bool)true, (bool)true);

	expect_neq("expect_eq(impl int)", -42, -42);
	expect_neq("expect_eq(expl int)", (int)-42, (int)-42);
	expect_neq("expect_eq(expl signed int)", (signed int)-42, (signed int)-42);
	expect_neq("expect_eq(expl unsigned int)", (unsigned int)42, (unsigned int)42);

	expect_neq("expect_eq(expl long)", (long)-42, (long)-42);
	expect_neq("expect_eq(expl signed long)", (signed long)-42, (signed long)-42);
	expect_neq("expect_eq(expl unsigned long)", (unsigned long)42, (unsigned long)42);

	expect_neq("expect_eq(expl long long)", (long long)-42, (long long)-42);
	expect_neq("expect_eq(expl signed long long)", (signed long long)-42, (signed long long)-42);
	expect_neq("expect_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)42);

	expect_neq("expect_eq(expl size_t)", (size_t)42, (size_t)42);

	expect_neq("expect_eq(impl NULL *)", NULL, NULL);
	expect_neq("expect_eq(expl NULL *)", (void *)NULL, (void *)NULL);

	int stack = 0;
	expect_neq("expect_eq(impl stack *)", &stack, &stack);
	expect_neq("expect_eq(expl stack int *)", (int *)&stack, (int *)&stack);
	expect_neq("expect_eq(expl stack void *)", (void *)&stack, (void *)&stack);

	int *heap;
	heap = malloc(sizeof(int));
	expect_neq("expect_eq(impl heap *)", &heap, &heap);
	expect_neq("expect_eq(expl heap int *)", (int *)&heap, (int *)&heap);
	expect_neq("expect_eq(expl heap void *)", (void *)&heap, (void *)&heap);
	free (heap);

	expect_neq("expect_eq(impl char *)", "42", "42");
	expect_neq("expect_eq(expl char *)", (char *)"42", (char *)"42");
	expect_neq("expect_eq(expl signed char *)", (signed char *)"42", (signed char *)"42");
	expect_neq("expect_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"42");
}

Test(neq_pass, 0)
{
	expect_neq("expect_eq(impl char)", 'a', 'b');
	expect_neq("expect_eq(expl char)", (char)'a', (char)'b');
	expect_neq("expect_eq(expl signed char)", (signed char)'a', (signed char)'b');
	expect_neq("expect_eq(expl unsigned char)", (unsigned char)'a', (unsigned char)'b');

	expect_neq("expect_eq(expl short)", (short)-42, (short)-1);
	expect_neq("expect_eq(expl signed short)", (signed short)-42, (signed short)-1);
	expect_neq("expect_eq(expl unsigned short)", (unsigned short)42, (unsigned short)1);

	expect_neq("expect_eq(impl bool)", true, false);
	expect_neq("expect_eq(expl bool)", (bool)true, (bool)false);

	expect_neq("expect_eq(impl int)", -42, -1);
	expect_neq("expect_eq(expl int)", (int)-42, (int)-1);
	expect_neq("expect_eq(expl signed int)", (signed int)-42, (signed int)-1);
	expect_neq("expect_eq(expl unsigned int)", (unsigned int)42, (unsigned int)1);

	expect_neq("expect_eq(expl long)", (long)-42, (long)-1);
	expect_neq("expect_eq(expl signed long)", (signed long)-42, (signed long)-1);
	expect_neq("expect_eq(expl unsigned long)", (unsigned long)42, (unsigned long)1);

	expect_neq("expect_eq(expl long long)", (long long)-42, (long long)-1);
	expect_neq("expect_eq(expl signed long long)", (signed long long)-42, (signed long long)-1);
	expect_neq("expect_eq(expl unsigned long long)", (unsigned long long)42, (unsigned long long)1);

	expect_neq("expect_eq(expl size_t)", (size_t)42, (size_t)1);

	int stack = 0;
	expect_neq("expect_eq(impl stack *)", &stack, NULL);
	expect_neq("expect_eq(expl stack int *)", (int *)&stack, (int *)NULL);
	expect_neq("expect_eq(expl stack void *)", (void *)&stack, (void *)NULL);

	int *heap;
	heap = malloc(sizeof(int));
	expect_neq("expect_eq(impl heap *)", &heap, NULL);
	expect_neq("expect_eq(expl heap int *)", (int *)&heap, (int *)NULL);
	expect_neq("expect_eq(expl heap void *)", (void *)&heap, (void *)NULL);
	free (heap);

	expect_neq("expect_eq(impl char *)", "42", "1");
	expect_neq("expect_eq(expl char *)", (char *)"42", (char *)"1");
	expect_neq("expect_eq(expl signed char *)", (signed char *)"42", (signed char *)"1");
	expect_neq("expect_eq(expl unsigned char *)", (unsigned char *)"42", (unsigned char *)"1");
}

Test(time_out, 1)
{
	int	i = 0;

	(void)i;
	while (true)
		i++;
}

Test(crash, 0)
{
	char	oops;
	int 	i		= 0;
	char 	segv[]	= "";

	(void)oops;
	(void)i;
	while(true)
		oops = segv[i++];
}
