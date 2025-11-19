#ifndef ULT_ASSERT_PUB_H
#define ULT_ASSERT_PUB_H

#include "capture_pub.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum e_format {
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING,
	F_STRUCT
}	t_format;

typedef struct s_assert
{
	t_capture_mode	mode;
	bool			eq;
	const char		*got_name;
	const char		*exp_name;
	t_capture		*got_capt;
	t_capture		*exp_capt;
	t_format		format;
	size_t			ret_size;
}	t_assert;

void	_fut_assert_run(t_assert *assert);

#define _fut_assert(should_be_equal, cap_mode, time_out, got_expr, exp_expr)		\
	do {																			\
	t_capture _fut_capt_got = {0};													\
	capture(cap_mode, time_out, (got_expr), _fut_capt_got);							\
																					\
	t_capture _fut_capt_exp = {0};													\
	capture(cap_mode, time_out, (exp_expr), _fut_capt_exp);							\
																					\
	t_assert _fut_assert = {0};														\
	_fut_assert.mode = cap_mode;													\
	_fut_assert.eq = should_be_equal;												\
	_fut_assert.got_name = #got_expr;												\
	_fut_assert.exp_name = #exp_expr;												\
	_fut_assert.got_capt = &_fut_capt_got;											\
	_fut_assert.exp_capt = &_fut_capt_exp;											\
	if (__type_is_void(exp_expr) && __type_is_void(got_expr))						\
	{																				\
		_fut_assert.ret_size = sizeof(int);											\
		_fut_assert.format = F_SIGNED;												\
	}																				\
	else																			\
	{																				\
		_fut_assert.ret_size = sizeof(__typeof__(exp_expr)); 						\
		_fut_assert.format = _Generic((exp_expr), 									\
				char: F_CHAR, 														\
				signed char: F_SIGNED, 												\
				short: F_SIGNED, 													\
				int: F_SIGNED, 														\
				long: F_SIGNED, 													\
				long long: F_SIGNED, 												\
				unsigned char: F_UNSIGNED, 											\
				unsigned short: F_UNSIGNED, 										\
				unsigned int: F_UNSIGNED, 											\
				unsigned long: F_UNSIGNED, 											\
				unsigned long long: F_UNSIGNED, 									\
				char *: F_STRING,													\
				const char *: F_STRING,												\
				default: F_STRUCT);													\
	}																				\
	_fut_assert_run(&_fut_assert);													\
	} while (0)

#define assert_eq(cap_mode, time_out, got_expr, exp_expr)		\
	_fut_assert(true, cap_mode, time_out, got_expr, exp_expr)
#define assert_neq(cap_mode, time_out, got_expr, exp_expr)	\
	_fut_assert(false, cap_mode, time_out, got_expr, exp_expr)
#define compare(cap_mode, time_out, fn1_name, fn2_name, fn_args)	\
	assert_eq(cap_mode, time_out, fn1_name fn_args, fn2_name fn_args)

#endif
