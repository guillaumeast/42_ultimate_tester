#ifndef ULT_SET_PUB_H
# define ULT_SET_PUB_H

# include <stddef.h>

#if defined(__APPLE__)
	# define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	# define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

typedef void (*t_test_fn)(void);

typedef enum e_status
{
	QUEUED,
	RUNNING,
	DONE,
}	t_status;

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

typedef struct s_set
{
	char		*name;
	size_t		timeout;
	t_status	status;
	t_test_fn	func;
	t_result	result;
}	t_set;

// Usage: Test(const char *name, size_t timeout)
# define Test(name, timeout) 				\
	static void name(void); 				\
	static t_set ULT_SECTION t_##name =		\
	{										\
		#name,								\
		timeout,							\
		QUEUED,								\
		name,								\
		{0, 0, 0, 0, 0}						\
	};										\
	static void name(void)

#endif
