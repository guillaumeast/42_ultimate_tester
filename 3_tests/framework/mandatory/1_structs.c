#include "ft_ultimate_tester.h"

// typedef struct s_test
// {
// 	size_t	a;
// 	size_t	b;
// 	size_t	c;
// 	size_t	d;
// }	t_test;

// t_test	*func_1(size_t a, size_t b)
// {
// 	static t_test test;

// 	test.a = a;
// 	test.b = b;
// 	test.c = a + b;
// 	test.d = a * b;
// 	return (&test);
// }

// t_test	*func_2(size_t a, size_t b)
// {
// 	static t_test test;

// 	test.a = a;
// 	test.b = b;
// 	test.c = a + b;
// 	test.d = a * b;
// 	return (&test);
// }

// Test(struct_same, 0)
// {
// 	t_test	test_a;
// 	t_test	test_b;

// 	test_a.a = 1;
// 	test_a.b = 2;
// 	test_a.c = 3;
// 	test_a.d = 2;
// 	test_b.a = 1;
// 	test_b.b = 2;
// 	test_b.c = 3;
// 	test_b.d = 2;
// 	assert_eq(RET, 0, &test_a, &test_a);						// should PASS -> is PASS
// 	assert_neq(RET, 0, &test_a, &test_a);						// should FAIL -> is FAIL
// 	assert_eq(RET, 0, &test_a, &test_b);						// should PASS -> is FAIL (wrong!)
// 	assert_neq(RET, 0, &test_a, &test_b);						// should FAIL -> is PASS (wrong!)
// }

// Test(struct_diff, 0)
// {
// 	t_test	test_a;
// 	t_test	test_b;

// 	test_a.a = 1;
// 	test_a.b = 2;
// 	test_a.c = 3;
// 	test_a.d = 4;
// 	test_b.a = 1;
// 	test_b.b = 2;
// 	test_b.c = 5;
// 	test_b.d = 6;
// 	assert_eq(RET, 0, &test_a, &test_a);						// should PASS -> is PASS
// 	assert_neq(RET, 0, &test_a, &test_a);						// should FAIL -> is FAIL
// 	assert_eq(RET, 0, &test_a, &test_b);						// should FAIL -> is FAIL
// 	assert_neq(RET, 0, &test_a, &test_b);						// should PASS -> is PASS
// }

// Test(struct_from_fn_ok, 0)
// {
// 	assert_eq(RET, 0, func_1(1, 2), func_2(1, 2));		// should PASS -> is PASS
// 	assert_neq(RET, 0, func_1(1, 2), func_2(1, 2));	// should FAIL -> is FAIL
// }

// Test(struct_from_fn_bug, 0)
// {
// 	assert_eq(RET, 0, func_1(1, 2), func_2(2, 3));		// should FAIL -> is PASS (wrong!)
// 	assert_neq(RET, 0, func_1(1, 2), func_2(2, 3));	// should PASS -> is FAIL (wrong!)
// }
