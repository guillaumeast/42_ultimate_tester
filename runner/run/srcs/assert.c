#include "assert_pub.h"
#include "set_priv.h"
#include "file_priv.h"
#include <inttypes.h>
#include <string.h>

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format fmt);
static inline void	log_fail(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);

void	ult_assert_run(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	if (ult_check(got, exp, fmt) == eq)
		g_result.passed++;
	else
	{
	 	g_result.failed++;
		log_fail(eq, name, got, exp, fmt);
	}
}

static inline bool	ult_check(intptr_t got, intptr_t exp, t_format format)
{
	if (format != F_STRING)
	 	return (got == exp);
	if (!got || !exp)
		return (!got && !exp);
	return (strcmp((const char *)got, (const char *)exp) == 0);
}

static inline void	log_fail(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	const char	*format;

	if (fmt == F_SIGNED)			format = "%" PRIdPTR;
	else if (fmt == F_UNSIGNED)	format = "%" PRIuPTR;
	else if (fmt == F_HEX)		format = "%" PRIxPTR;
	else if (fmt == F_CHAR)		format = "%c";
	else if (fmt == F_STRING)	format = "%s";
	else							format = "%" PRIxPTR;

	flush_all();
	fprintf(stderr, " |   ⤷ ✖ %s = ", name);
	fprintf(stderr, format, got);
	fprintf(stderr, eq ? " (expected " : " (expected ≠ ");
	fprintf(stderr, format, exp);
	fprintf(stderr, ")\n");
	flush_all();
}
