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
	F_STRING
}	t_format;

void	_fut_assert_run(	\
	bool eq, 				\
	const char *got_name, 	\
	const char *exp_name, 	\
	t_capture *got, 		\
	t_capture *exp, 		\
	t_format fmt			\
);

#define _fut_assert(should_be_equal, mode, timeout, got, exp)			\
	do {																\
	t_capture capt_got = {0};											\
	capture(mode, timeout, got, &capt_got);						\
																		\
	t_capture capt_exp = {0};											\
	capture(mode, timeout, exp, &capt_exp);						\
																		\
	_fut_assert_run(should_be_equal, #got, #exp, &capt_got, &capt_exp,	\
		_Generic((exp), 												\
			char: F_CHAR, 												\
			signed char: F_SIGNED, 										\
			short: F_SIGNED, 											\
			int: F_SIGNED, 												\
			long: F_SIGNED, 											\
			long long: F_SIGNED, 										\
			unsigned char: F_UNSIGNED, 									\
			unsigned short: F_UNSIGNED, 								\
			unsigned int: F_UNSIGNED, 									\
			unsigned long: F_UNSIGNED, 									\
			unsigned long long: F_UNSIGNED, 							\
			char *: F_STRING,											\
			const char *: F_STRING,										\
			default: F_HEX))											\
	} while (0)

#define assert_eq(mode, timeout, got, expected)		\
	_fut_assert(true, mode, timeout, got, expected)
#define assert_neq(mode, timeout, got, expected)	\
	_fut_assert(false, mode, timeout, got, expected)
#define compare(mode, timeout, fn1_name, fn2_name, fn_args)	\
	assert_eq(mode, timeout, fn1_name fn_args, fn2_name fn_args)

#endif
