#ifndef ULT_ASSERT_PUB_H
#define ULT_ASSERT_PUB_H

#include <stdbool.h>
#include <stdint.h>

typedef enum e_format {
	F_SIGNED,
	F_UNSIGNED,
	F_HEX,
	F_CHAR,
	F_STRING
}	t_format;

void	assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);
void	print_assert_failed(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);

#define _ult_assert(should_be_equal, name, got, expected) \
	assert_run(should_be_equal, name, (intptr_t)(got), (intptr_t)(expected), _Generic((expected), \
			char: F_CHAR, \
			signed char: F_SIGNED, \
			short: F_SIGNED, \
			int: F_SIGNED, \
			long: F_SIGNED, \
			long long: F_SIGNED, \
			unsigned char: F_UNSIGNED, \
			unsigned short: F_UNSIGNED, \
			unsigned int: F_UNSIGNED, \
			unsigned long: F_UNSIGNED, \
			unsigned long long: F_UNSIGNED, \
			char *: F_STRING, \
			const char *: F_STRING, \
			default: F_HEX))
#define assert_eq(name, got, expected) _ult_assert(true, name, got, expected)
#define assert_neq(name, got, expected) _ult_assert(false, name, got, expected)

#endif
