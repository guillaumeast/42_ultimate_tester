#ifndef FUT_H
#define FUT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

/*---------- status/status_pub.h ----------*/

#define STATUS_BUFFER_SIZE 32

typedef enum e_status_type
{
	QUEUED,
	RUNNING,
	PASSED,
	FAILED,
	TIMED,
	CRASHED,
	LEAKED,
	DONE,	
}	t_status_type;

typedef struct s_status
{
	t_status_type	type;
	int				sig;
	void			*crash_address;
	size_t			timeout;
}	t_status;

/*---------- result/result_pub.h ----------*/

typedef struct s_result
{
	t_status	status;
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
	size_t		leaks;
}	t_result;

void	result_compute(t_result *res);
void	result_add(const t_result *from, t_result *to);

/*---------- io/redirect_pub.h ----------*/

typedef enum e_redirect_mode
{
	R_STDOUT,
	R_STDERR,
	R_BOTH
}	t_redirect_mode;

void	redirect_start(t_redirect_mode mode);
char	*redirect_read(void);
void	redirect_stop(void);

#define get_output(mode, expression, var_name)	\
	do											\
	{											\
		redirect_start(mode);					\
		expression;								\
		var_name = redirect_read();				\
		redirect_stop();						\
	} while (0)

/*---------- io/print_wrapper_pub.h ----------*/

__attribute__((format(printf, 1, 2)))
void	print_stdout(const char *fmt, ...);
__attribute__((format(printf, 1, 2)))
void	print_stderr(const char *fmt, ...);

/*---------- process/context_pub.h ----------*/

typedef struct s_context
{
	bool	has_parent;
	bool	has_child;
	pid_t	child_pid;
	size_t	child_timeout;
	int		pipe_to_parent[2];
	int		pipe_to_child[2];
}	t_context;

extern t_context	g_context;

/*---------- process/fork_pub.h ----------*/

void	_fork_init(size_t timeout);

/*---------- logs/format_pub.h ----------*/

typedef enum e_format {
	F_BOOL,
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING,
	F_STRUCT
}	t_format;

/*---------- engine/set_pub.h ----------*/

#if defined(__APPLE__)
	#define ULT_SECTION __attribute__((used, section("__DATA,__ult_tester")))
#else
	#define ULT_SECTION __attribute__((section(".ult_tester")))
#endif

typedef void (*t_test_fn)(void);

typedef struct s_set
{
	const char	*name;
	size_t		timeout;
	t_test_fn	func;
	t_result	result;
}	t_set;

#define Test(name, timeout_sec) 						\
	static void name(void); 							\
	static t_set ULT_SECTION _##name##__##__COUNTER__ =	\
	{													\
		#name,											\
		timeout_sec,									\
		name,											\
		{ {QUEUED, 0, 0, 0}, 0, 0, 0, 0, 0, 0 }			\
	};													\
	static void name(void)

/*---------- engine/memcheck_pub.h ----------*/

typedef enum e_mem_mode
{
	LEAKS,
	SAFETY,
}	t_mem_mode;

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	_memcheck_parent(const char *expr);
void	_memcheck_enable(t_mem_mode mode);
void	_memcheck_child(const char *expr);

#define memleaks(timeout_sec, expression)	\
	do {									\
		_fork_init(timeout_sec);			\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expression);	\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(LEAKS);		\
			expression;						\
			_memcheck_child(#expression);	\
		}									\
	} while (0)

#define memsafety(timeout_sec, expression)	\
	do {									\
		_fork_init(timeout_sec);			\
		if (g_context.child_pid > 0)		\
			_memcheck_parent(#expression);	\
		if (g_context.child_pid == 0)		\
		{									\
			_memcheck_enable(SAFETY);		\
			expression;						\
			_memcheck_child(#expression);	\
		}									\
	} while (0)

/*---------- engine/capture_pub.h ----------*/

typedef enum e_capture_mode
{
	RET,
	OUT,
	ERR,
	BOTH,
	RET_OUT,
	RET_ERR,
	RET_BOTH,
}	t_capture_mode;

static const t_redirect_mode g_capture_to_redirect[] = {
	[RET]		= -1,
    [OUT]       = R_STDOUT,
    [ERR]       = R_STDERR,
    [BOTH]      = R_BOTH,
    [RET_OUT]   = R_STDOUT,
    [RET_ERR]   = R_STDERR,
    [RET_BOTH]  = R_BOTH
};

typedef struct s_capture {
	t_status	status;
	intptr_t	ret;
	char		*out;
} t_capture;

typedef struct s_capture_res
{
	intptr_t	ret;
	char		*out;
}	t_capture_res;

void	_capture_parent(t_capture *capture);
void	_capture_child(t_capture_res *res);

#define __type_is_void(expr) __builtin_types_compatible_p(__typeof__(expr), void)
#define __expr_or_zero(expr) __builtin_choose_expr(__type_is_void(expr), 0, (expr))
#define CAP_VOID(expr, dest) ({ (void)(expr); (dest) = 0; 0; })
#define CAP_VALUE(expr, dest) ({ (dest) = (intptr_t)(__expr_or_zero(expr)); 0; })
#define CAP_DISPATCH(expr, dest)				\
	__builtin_choose_expr(__type_is_void(expr),	\
		CAP_VOID(expr, dest),					\
		CAP_VALUE(expr, dest))

#define capture(mode, timeout_sec, expr, capture_var_name)		\
	do {														\
		memset(&capture_var_name, 0, sizeof capture_var_name);	\
		capture_var_name.status.timeout = timeout_sec;			\
		_fork_init(timeout_sec);								\
		if (g_context.child_pid > 0)							\
			_capture_parent(&capture_var_name);					\
		else													\
		{														\
			t_capture_res capture_res = {0};					\
			if (mode != RET)									\
				redirect_start(g_capture_to_redirect[mode]);	\
			CAP_DISPATCH(expr, capture_res.ret);				\
			if (mode != RET)									\
			{													\
				capture_res.out = redirect_read();				\
				redirect_stop();								\
			}													\
			_capture_child(&capture_res);						\
		}														\
	} while (0)

/*---------- engine/assert_pub.h ----------*/

typedef struct s_assert
{
	t_capture_mode	mode;
	bool			eq;
	const char		*lab;
	t_capture		*got_capt;
	t_capture		*exp_capt;
	t_format		format;
	size_t			ret_size;
}	t_assert;

void	_assert_run(t_assert *assert);

#define _assert(should_be_equal, cap_mode, timeout_sec, label, got_expr, exp_expr)	\
	do {																			\
		t_capture _capt_got = {0};													\
		capture(cap_mode, timeout_sec, (got_expr), _capt_got);						\
																					\
		t_capture _capt_exp = {0};													\
		capture(cap_mode, timeout_sec, (exp_expr), _capt_exp);						\
																					\
		t_assert _assert = {0};														\
		_assert.mode = cap_mode;													\
		_assert.eq = should_be_equal;												\
		_assert.lab = label;														\
		_assert.got_capt = &_capt_got;												\
		_assert.exp_capt = &_capt_exp;												\
		if (__type_is_void(exp_expr) && __type_is_void(got_expr))					\
		{																			\
			_assert.ret_size = sizeof(int);											\
			_assert.format = F_SIGNED;												\
		}																			\
		else																		\
		{																			\
			_assert.ret_size = sizeof(__typeof__(exp_expr)); 						\
			_assert.format = _Generic(__typeof__(exp_expr), 						\
				bool: F_BOOL, 														\
				char: F_CHAR, 														\
				unsigned char: F_CHAR, 												\
				signed char: F_CHAR, 												\
				short: F_SIGNED, 													\
				unsigned short: F_UNSIGNED, 										\
				int: F_SIGNED, 														\
				unsigned int: F_UNSIGNED, 											\
				long: F_SIGNED, 													\
				unsigned long: F_UNSIGNED, 											\
				long long: F_SIGNED, 												\
				unsigned long long: F_UNSIGNED, 									\
				char *: F_STRING,													\
				char []: F_STRING,													\
				const char *: F_STRING,												\
				const char []: F_STRING,											\
				unsigned char *: F_STRING,											\
				unsigned char []: F_STRING,											\
				const unsigned char *: F_STRING,									\
				const unsigned char []: F_STRING,									\
				void *: F_HEX,														\
				const void *: F_HEX,												\
				default: F_HEX);													\
		}																			\
		_assert_run(&_assert);														\
	} while (0)

#define assert(timeout_sec, expression)													\
	_assert(true, RET, timeout_sec, #expression, expression, (bool)true)
#define assert_label(timeout_sec, label, expression)									\
	_assert(true, RET, timeout_sec, label, expression, (bool)true)

#define assert_eq(cap_mode, timeout_sec, got_expression, exp_expression)				\
	_assert(true, cap_mode, timeout_sec, #got_expression, got_expression, exp_expression)
#define assert_eq_label(cap_mode, timeout_sec, label, got_expression, exp_expression)	\
	_assert(true, cap_mode, timeout_sec, label, got_expression, exp_expression)

#define assert_neq(cap_mode, timeout_sec, got_expression, exp_expression)				\
	_assert(false, cap_mode, timeout_sec, #got_expression, got_expression, exp_expression)
#define assert_neq_label(cap_mode, timeout_sec, label, got_expression, exp_expression)	\
	_assert(false, cap_mode, timeout_sec, label, got_expression, exp_expression)

#define compare(cap_mode, timeout_sec, fn1_name, fn2_name, fn_args)						\
	_assert(true, cap_mode, timeout_sec, #fn1_name#fn_args, fn1_name fn_args, fn2_name fn_args)
#define compare_label(cap_mode, timeout_sec, label, fn1_name, fn2_name, fn_args)		\
	_assert(true, cap_mode, timeout_sec, label, fn1_name fn_args, fn2_name fn_args)

#endif
