#include "run.h"

extern size_t g_total;
extern size_t g_passed;
extern size_t g_failed;
extern size_t g_timed_out;
extern size_t g_crashed;

static t_set *g_current_set = NULL;
t_set	*get_current_set() { return (g_current_set); }
void	set_current_set(t_set *set) { g_current_set = set; }

static inline void	test_add_to_total(t_test *test);

void	test_init(t_set *set, t_test *test)
{
	test->set = set;
	test->status = QUEUED;
	test->type = set->type;
	test->timeout = set->timeout;
	test->fake_stdout.original_fd_copy = -1;
	test->fake_stdout.tmp_fd = -1;
	test->fake_stdout.tmp_file = NULL;
	test->fn1.fn = (int (*)(const char *, ...))set->fn1;
	test->fn1.out = NULL;
	test->fn1.ret = 0;
	test->fn2.fn = (int (*)(const char *, ...))set->fn2;
	test->fn2.out = NULL;
	test->fn2.ret = 0;
}

void	test_check(t_test *test)
{
	bool success;

	if (test->status != QUEUED)
		return ;
	test->status = RUNNING;
	success = false;

	if (test->type == COMPARE_OUTPUTS)
		success = ft_strcmp(test->fn1.out, test->fn2.out);
	else if (test->type == COMPARE_RETURNS)
		success = (test->fn1.ret == test->fn2.ret);
	else
		success = ft_strcmp(test->fn1.out, test->fn2.out) \
						&& (test->fn1.ret == test->fn2.ret);
	
	if (success)
		test->status = PASSED;
	else
	 	test->status = FAILED;

	test_add_to_total(test);
}

static inline void	test_add_to_total(t_test *test)
{
	switch (test->status)
	{
		case PASSED:	g_passed++;		break;
		case FAILED:	g_failed++;		break;
		case TIMED_OUT:	g_timed_out++;	break;
		case CRASHED:	g_crashed++;	break;
		case QUEUED:
		case RUNNING:
		default:						break;
	}
	g_total++;
}
