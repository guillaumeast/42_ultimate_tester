#ifndef ULT_ASSERT_PUB_H
#define ULT_ASSERT_PUB_H

#include "format_pub.h"
#include "capture_pub.h"
#include <stdbool.h>
#include <stdint.h>

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

#define _assert(should_be_equal, cap_mode, timeout_sec, label, got_expr, exp_expr)				\
	do {																						\
		t_capture _capt_got = {0};																\
		capture(cap_mode, timeout_sec, (got_expr), _capt_got);									\
																								\
		t_capture _capt_exp = {0};																\
		capture(cap_mode, timeout_sec, (exp_expr), _capt_exp);									\
																								\
		t_assert _assert = {0};																	\
		_assert.mode = cap_mode;																\
		_assert.eq = should_be_equal;															\
		_assert.lab = label;																	\
		_assert.got_capt = &_capt_got;															\
		_assert.exp_capt = &_capt_exp;															\
		if (__type_is_void(exp_expr) && __type_is_void(got_expr))								\
		{																						\
			_assert.ret_size = sizeof(int);														\
			_assert.format = F_SIGNED;															\
		}																						\
		else																					\
		{																						\
			_assert.ret_size = sizeof(__typeof__(exp_expr)); 									\
			if (__builtin_types_compatible_p(__typeof__(exp_expr), bool))						\
				_assert.format = F_BOOL;														\
			else if (																			\
				__builtin_types_compatible_p(__typeof__(exp_expr), char) ||						\
				__builtin_types_compatible_p(__typeof__(exp_expr), signed char) ||				\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned char)				\
			)																					\
				_assert.format = F_CHAR;														\
			else if (																			\
				__builtin_types_compatible_p(__typeof__(exp_expr), short) ||					\
				__builtin_types_compatible_p(__typeof__(exp_expr), int) ||						\
				__builtin_types_compatible_p(__typeof__(exp_expr), long) ||						\
				__builtin_types_compatible_p(__typeof__(exp_expr), long long)					\
			)																					\
				_assert.format = F_SIGNED;														\
			else if (																			\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned short) ||			\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned int) ||				\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned long) ||			\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned long long)			\
			)																					\
				_assert.format = F_UNSIGNED;													\
			else if (																			\
				__builtin_types_compatible_p(__typeof__(exp_expr), char *) ||					\
				__builtin_types_compatible_p(__typeof__(exp_expr), char []) ||					\
				__builtin_types_compatible_p(__typeof__(exp_expr), const char *) ||				\
				__builtin_types_compatible_p(__typeof__(exp_expr), const char []) ||			\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned char *) ||			\
				__builtin_types_compatible_p(__typeof__(exp_expr), unsigned char []) ||			\
				__builtin_types_compatible_p(__typeof__(exp_expr), const unsigned char *) ||	\
				__builtin_types_compatible_p(__typeof__(exp_expr), const unsigned char [])		\
			)																					\
				_assert.format = F_STRING;														\
			else if (																			\
				__builtin_types_compatible_p(__typeof__(exp_expr), void *) ||					\
				__builtin_types_compatible_p(__typeof__(exp_expr), const void *)				\
			)																					\
				_assert.format = F_HEX;															\
			else																				\
				_assert.format = F_HEX;															\
		}																						\
		_assert_run(&_assert);																	\
	} while (0)

#define assert(timeout_sec, expr)													\
	_assert(true, RET, timeout_sec, #expr, expr, (bool)true)
#define assert_label(timeout_sec, label, expr)										\
	_assert(true, RET, timeout_sec, label, expr, (bool)true)

#define assert_eq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(true, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_eq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(true, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define assert_neq(cap_mode, timeout_sec, got_expr, exp_expr)						\
	_assert(false, cap_mode, timeout_sec, #got_expr, got_expr, exp_expr)
#define assert_neq_label(cap_mode, timeout_sec, label, got_expr, exp_expr)			\
	_assert(false, cap_mode, timeout_sec, label, got_expr, exp_expr)

#define compare(cap_mode, timeout_sec, fn1_name, fn2_name, fn_args)					\
	_assert(true, cap_mode, timeout_sec, #fn1_name#fn_args, fn1_name fn_args, fn2_name fn_args)
#define compare_label(cap_mode, timeout_sec, label, fn1_name, fn2_name, fn_args)	\
	_assert(true, cap_mode, timeout_sec, label, fn1_name fn_args, fn2_name fn_args)

#endif
