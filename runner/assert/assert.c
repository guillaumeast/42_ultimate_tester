#define __FUT_INSIDE__
#include "assert_pub.h"
#include "print_priv.h"
#include "set_priv.h"
#include "file_priv.h"
#undef __FUT_INSIDE__

#include <inttypes.h>
#include <string.h>

static inline bool	assert_check(intptr_t got, intptr_t exp, t_format fmt);

void	assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	if (assert_check(got, exp, fmt) == eq)
		g_set.result.passed++;
	else
	{
		g_set.result.failed++;
		print_assert_failed(eq, name, got, exp, fmt);
	}
	g_set.result.total++;
}

static inline bool	assert_check(intptr_t got, intptr_t exp, t_format format)
{
	if (format != F_STRING)
	 	return (got == exp);
	if (!got || !exp)
		return (!got && !exp);
	return (strcmp((const char *)got, (const char *)exp) == 0);
}

void	print_assert_failed(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	const char	*format;

	if (fmt == F_SIGNED)		format = "%" PRIdPTR;
	else if (fmt == F_UNSIGNED)	format = "%" PRIuPTR;
	else if (fmt == F_HEX)		format = "%" PRIxPTR;
	else if (fmt == F_CHAR)		format = "%c";
	else if (fmt == F_STRING)	format = "%s";
	else						format = "%" PRIxPTR;

	print_stderr(" %s|%s     %s %s %s%s %s=%s ", BLUE, RED, EMJ_ARW_DR, EMJ_FAIL, YELLOW, name, NONE, RED);
	print_stderr(format, got);
	if (eq)
		print_stderr("%s (expected %s", NONE, RED);
	else
		print_stderr("%s (expected != %s", NONE, RED);
	print_stderr(format, exp);
	print_stderr("%s)\n", NONE);
}

// TODO: compare structs with memcopy (sizeof struct) !! marche uniquement si pas de pointeurs dans la struct
