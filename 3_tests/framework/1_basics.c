#include "ft_ultimate_tester.h"
#include "libftprintf.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void fake_fn(const char *str)
{
	(void)str;
	printf("hey");
}

void fake_fn2(const char *s1, const char *s2)
{
	(void)s1;
	(void)s2;
	printf("hey 2");
}

void	my_void_func(void)
{
	printf("Hello World");
}

int	add(int a, int b)
{
	return (a + b);
}

void just_timeout_bro(void)
{
	int	i = 0;

	(void)i;
	while (true)
		i++;
}

void just_crash_bro(void)
{
	volatile int *oops;

	oops = NULL;
	*oops = 42;
}

void just_timeout_with_arg(int i)
{
	(void)i;
	while (true)
		i++;
}

void just_crash_with_arg(int i)
{
	volatile int *oops;

	oops = NULL;
	*oops = i;
}

/* -------------------- ASSERT & REDIRECT -------------------- */

Test(generic_assert_check, 0)
{
	assert(1, just_timeout_bro());									// TIMED
	assert(0, add(1, 2) > 2 && add(1, 2) < 4);						// PASS
	assert(0, add(1, 2) > 3 && add(1, 2) < 4);						// FAIL
	redirect_start(R_STDOUT);
	assert(0, printf("Hello World") == ft_printf("Hello World"));	// PASS
	assert(0, printf("Hello World") == ft_printf("Not same ret"));	// FAIL
	redirect_stop();
}

/* -------------------- GET_OUTPUT -------------------- */

Test(get_output_check, 0)
{
	char *out1;
	char *out2;
	get_output(R_STDOUT, printf("Hello World"), out1);
	get_output(R_STDOUT, ft_printf("Hello World"), out2);
	assert_eq(RET, 0, out1, out2);							// PASS
	assert(0, strcmp(out1, out2) == 0);			// PASS
	get_output(R_STDOUT, printf("Hello World"), out1);
	get_output(R_STDOUT, ft_printf("Not sameout"), out2);
	assert_eq(RET, 0, out1, out2);							// FAIL
}

/* -------------------- CONST HANDLING -------------------- */

Test(nonvoid_and_constant, 0)
{
	assert_eq(RET, 1, add(1,2), 3);			// TRUE
	assert_neq(RET, 1, add(1,2), 4);			// TRUE
	assert_eq(OUT, 1, add(1,2), 3);			// TRUE
	assert_eq(OUT, 1, add(1,2), 4);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), 3);		// TRUE

	assert_neq(RET, 1, add(1,2), 3);			// FALSE
	assert_eq(RET, 1, add(1,2), 4);			// FALSE
	assert_neq(OUT, 1, add(1,2), 3);			// FALSE
	assert_neq(OUT, 1, add(1,2), 4);			// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), 3);	// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), 4);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), 4);	// FALSE

	// TRUE = 5 | FALSE = 7
}

/* -------------------- VAR HANDLING -------------------- */

Test(nonvoid_and_var, 0)
{
	int exp = 3;

	assert_eq(RET, 1, add(1,2), exp);			// TRUE
	assert_eq(OUT, 1, add(1,2), exp);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), exp);		// TRUE
	assert_neq(RET, 1, add(1,2), exp);			// FALSE
	assert_neq(OUT, 1, add(1,2), exp);			// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), exp);		// FALSE

	exp = 4;
	assert_neq(RET, 1, add(1,2), exp);			// TRUE
	assert_eq(OUT, 1, add(1,2), exp);			// TRUE
	assert_eq(RET, 1, add(1,2), exp);			// FALSE
	assert_neq(OUT, 1, add(1,2), exp);			// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), exp);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), exp);		// FALSE

	// TRUE = 5 | FALSE = 7
}

Test(nonvoid_and_unref, 0)
{
	int exp = 3;
	int *exp_p = &exp;

	assert_eq(RET, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(OUT, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(RET_BOTH, 1, add(1,2), *exp_p);	// TRUE
	assert_neq(RET, 1, add(1,2), *exp_p);		// FALSE
	assert_neq(OUT, 1, add(1,2), *exp_p);		// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE

	exp = 4;
	assert_neq(RET, 1, add(1,2), *exp_p);		// TRUE
	assert_eq(OUT, 1, add(1,2), *exp_p);			// TRUE
	assert_eq(RET, 1, add(1,2), *exp_p);			// FALSE
	assert_neq(OUT, 1, add(1,2), *exp_p);		// FALSE
	assert_eq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE
	assert_neq(RET_BOTH, 1, add(1,2), *exp_p);	// FALSE

	// TRUE = 5 | FALSE = 7
}

/* -------------------- TIME OUT -------------------- */

Test(test_time_out_after_asserts, 10)
{
	assert_eq(RET, 1, 1, just_timeout_bro());
	assert_eq(RET, 1, just_timeout_bro(), 1);
	assert_neq(RET, 1, just_timeout_bro(), just_timeout_bro());
}

Test(test_time_out_during_asserts, 4)
{
	assert_eq(RET, 2, 1, just_timeout_bro());
	assert_eq(RET, 2, just_timeout_bro(), 1);
	assert_neq(RET, 2, just_timeout_bro(), just_timeout_bro());
}

Test(test_time_out_before_asserts, 1)
{
	assert_eq(RET, 2, 1, just_timeout_bro());
	assert_eq(RET, 2, just_timeout_bro(), 1);
	assert_neq(RET, 2, just_timeout_bro(), just_timeout_bro());
}

/* -------------------- CRASH -------------------- */

Test(test_crash_after_asserts, 0)
{
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
	just_crash_bro();
}

Test(test_crash_during_asserts, 0)
{
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	just_crash_bro();
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
}

Test(test_crash_before_asserts, 0)
{
	just_crash_bro();
	assert_eq(RET, 0, 1, just_crash_bro());
	assert_eq(RET, 0, just_crash_bro(), 1);
	assert_neq(RET, 0, just_crash_bro(), just_crash_bro());
}

Test(void_func, 0)
{
	assert_eq(RET_BOTH, 1, my_void_func(), my_void_func());	// PASS
	assert_neq(RET_BOTH, 1, my_void_func(), my_void_func());	// FAIL
}

Test(variadic, 0)
{
	assert_eq(RET_BOTH, 1, printf("%i", 42), printf("%i", 42));	// PASS
	assert_eq(RET_BOTH, 1, printf("%i", 42), printf("%i", -42));	// FAIL
	assert_neq(RET_BOTH, 1, printf("%i", 42), printf("%i", -42));	// PASS
	assert_neq(RET_BOTH, 1, printf("%i", 42), printf("%i", 42));	// FAIL
}

Test(comparison_ok, 0)
{
	compare(RET_BOTH, 1, printf, ft_printf, ("Hello world"));			// PASS
	compare(RET_BOTH, 1, printf, ft_printf, ("%s", "Hello world"));	// PASS
	compare(RET_BOTH, 1, just_timeout_bro, just_timeout_bro, );				// PASS
	compare(RET_BOTH, 1, just_crash_bro, just_crash_bro, );					// PASS
	compare(RET_BOTH, 1, my_void_func, my_void_func, );						// PASS
	
	compare(RET_BOTH, 1, fake_fn, ft_printf, ("Hello world"));	// FAIL
	compare(RET_BOTH, 1, fake_fn2, ft_printf, ("%s", "Hello world"));	// FAIL
	compare(RET_BOTH, 1, just_timeout_bro, my_void_func, );					// FAIL
	compare(RET_BOTH, 1, just_crash_bro, my_void_func, );						// FAIL
	compare(RET_BOTH, 1, my_void_func, just_timeout_bro, );					// FAIL
	compare(RET_BOTH, 1, my_void_func, just_crash_bro, );						// FAIL
	compare(RET_BOTH, 1, just_timeout_bro, just_crash_bro, );					// FAIL
	compare(RET_BOTH, 1, just_crash_bro, just_timeout_bro, );					// FAIL
}

/* -------------------- SIGINT HANDLER -------------------- */

// Test(please_kill_me_to_test_SIGINT_handling, 0)
// {
// 	assert_eq(RET, 0, just_timeout_bro(), just_timeout_bro());
// }
