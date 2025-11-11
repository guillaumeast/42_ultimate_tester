#ifndef ULT_SET_H
# define ULT_SET_H

# include <stddef.h>

typedef void (*t_test_fn)(void);

typedef enum e_status
{
	QUEUED,
	RUNNING,
	DONE,
}	t_status;

typedef struct s_set
{
	char		*name;
	size_t		timeout;
	t_status	status;
	t_test_fn	func;
}	t_set;

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

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

# define Test(name, timeout) 				\
	static void name(void); 				\
	static t_set ULT_SECTION t_##name =		\
	{										\
		#name,								\
		timeout,							\
		QUEUED,								\
		name,								\
	};										\
	static void name(void)

void	run_all_sets(void);

#endif
