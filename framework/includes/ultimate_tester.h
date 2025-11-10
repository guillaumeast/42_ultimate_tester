#ifndef LIB_ULTIMATE_TESTER_H
# define LIB_ULTIMATE_TESTER_H

# include <stddef.h>
# include "types.h"
# include "utils.h"
# include "redirect.h"
# include "run.h"

#if defined(__APPLE__)
	# define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
    extern t_set __data_ult_tester_start[] __asm("section$start$__DATA$__ult_tester");
    extern t_set __data_ult_tester_end[]   __asm("section$end$__DATA$__ult_tester");
    # define START_SET __data_ult_tester_start
    # define STOP_SET  __data_ult_tester_end
#else
	# define ULT_SECTION __attribute__((section(".ult_tester")))
    extern t_set __start_ult_tester;
    extern t_set __stop_ult_tester;
    # define START_SET  &__start_ult_tester
    # define STOP_SET   &__stop_ult_tester
#endif

# define Compare(name, fn1, fn2, mode, timeout) \
	static void name(void); \
	static t_set ULT_SECTION t_##name = { \
		#name, \
		mode, \
		QUEUED, \
		timeout, \
		(int (*)(const char *, ...))fn1, \
		(int (*)(const char *, ...))fn2, \
		name \
	}; \
	static void name(void)


# define Try(...) do \
{ \
	t_test		test; \
	fprintf(stderr, "Starting runner...\n"); \
	test_init(get_current_set(), &test); \
	fprintf(stderr, "Set initialized...\n"); \
	if (test.type != COMPARE_RETURNS) \
		redirect_start(&(test.fake_stdout)); \
	fprintf(stderr, "Redirection started...\n"); \
	if (test.type != COMPARE_OUTPUTS) \
		test.fn1.ret = ((intptr_t (*)())test.fn1.fn)(__VA_ARGS__); \
	fprintf(stderr, "Fn1 returned value stored...\n"); \
	if (test.type != COMPARE_RETURNS) \
		redirect_read(&(test.fake_stdout), &(test.fn1.out)); \
	fprintf(stderr, "Fn1 output stored...\n"); \
	if (test.type != COMPARE_OUTPUTS) \
		test.fn2.ret = ((intptr_t (*)())test.fn2.fn)(__VA_ARGS__); \
	fprintf(stderr, "Fn2 returned value stored...\n"); \
	if (test.type != COMPARE_RETURNS) \
		redirect_read(&(test.fake_stdout), &(test.fn2.out)); \
	fprintf(stderr, "Fn1 output stored...\n"); \
	if (test.type != COMPARE_RETURNS) \
		redirect_stop(&(test.fake_stdout)); \
	fprintf(stderr, "Redirection stoped...\n"); \
	test_check(&test); \
	fprintf(stderr, "Test checked...\n"); \
	if (test.fn1.out) free(test.fn1.out); \
	if (test.fn2.out) free(test.fn2.out); \
	fprintf(stderr, "Ending runner...\n"); \
} while (0)


#endif

// TODO: expect_str_eq(const char *got, const char *expected)
// TODO: expect_str_neq(const char *got, const char *expected)
// TODO: expect_nbr_eq(intptr_t got, intptr_t expected)
// TODO: expect_nbr_neq(intptr_t got, intptr_t expected)
