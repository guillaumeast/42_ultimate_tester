do
{
	t_test		test;
	test_init(get_current_set(), &test);
	if (test.type != COMPARE_RETURNS) redirect_start(&(test.fake_stdout));
	if (test.type != COMPARE_OUTPUTS) test.fn1.ret = ((intptr_t (*)())test.fn1.fn)(__VA_ARGS__);
	if (test.type != COMPARE_RETURNS) redirect_read(&(test.fake_stdout), &(test.fn1.out));
	if (test.type != COMPARE_OUTPUTS) test.fn2.ret = ((intptr_t (*)())test.fn2.fn)(__VA_ARGS__);
	if (test.type != COMPARE_RETURNS) redirect_read(&(test.fake_stdout), &(test.fn2.out));
	if (test.type != COMPARE_RETURNS) redirect_stop(&(test.fake_stdout));
	test_check(&test);
	if (test.fn1.out) free(test.fn1.out);
	if (test.fn2.out) free(test.fn2.out);
} while (0)
