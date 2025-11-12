#include "assert_pub.h"
#include "print_priv.h"
#include "set_pub.h"
#include "file_priv.h"
#include <inttypes.h>
#include <string.h>

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format fmt);

void	ult_assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	if (ult_check(got, exp, fmt) == eq)
	{
		g_current_set->result.passed++;
		g_result.passed++;
	}
	else
	{
		g_current_set->result.failed++;
	 	g_result.failed++;
		print_assert_failed(eq, name, got, exp, fmt);
	}
	g_current_set->result.total++;
}

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format format)
{
	if (format != F_STRING)
	 	return (got == exp);
	if (!got || !exp)
		return (!got && !exp);
	return (strcmp((const char *)got, (const char *)exp) == 0);
}
