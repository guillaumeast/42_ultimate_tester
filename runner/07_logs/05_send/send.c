#define __FUT_INSIDE__
#define __FUT_MEMCHECK_INSIDE__
#include "process_priv.h"
#undef __FUT_MEMCHECK_INSIDE__
#undef __FUT_INSIDE__

#include <inttypes.h>
#include <stdio.h>

static inline void	add_formatted_value(char *buff, size_t cap, size_t *offset, t_format fmt, intptr_t value);

void	send_incorrect_status(t_context *ctx, const char *expr, t_status *got, t_status *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	offset = snprintf(log, sizeof log, "%s%s %s%s", RED, expr, YELLOW, format_status(got));
	if (got->crash_address)
		offset += snprintf(log + offset, sizeof log - offset, " %sat %s", GREY, format_addr(got->crash_address));
	if (exp)
		offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s%s", GREY, RED, format_status(exp));

	snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	message_send(ctx->pipe, LOG, (t_message_data *)log);
}

void	send_incorrect_return(t_context *ctx, const char *expr, t_format fmt, intptr_t got, intptr_t *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	offset = snprintf(log, sizeof log, "%s%s %s%s %s", RED, expr, YELLOW, "outputed", RED);
	add_formatted_value(log, sizeof log, &offset, fmt, got);
	if (exp)
	{
		offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s", GREY, RED);
		add_formatted_value(log, sizeof log, &offset, fmt, *exp);
	}

	snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	message_send(ctx->pipe, LOG, (t_message_data *)log);
}

void	send_incorrect_output(t_context *ctx, const char *expr, const char *got, const char *exp)
{
	char	log[H2_CAP];
	size_t	offset;

	offset = snprintf(log, sizeof log, "%s%s %s%s %s%s", RED, expr, YELLOW, "outputed", RED, got);
	if (exp)
		offset += snprintf(log + offset, sizeof log - offset, " %sinstead of %s%s", GREY, RED, exp);

	snprintf(log + offset, sizeof log - offset, "%s\n", NONE);
	message_send(ctx->pipe, LOG, (t_message_data *)log);
}

void	send_leak(t_context *ctx, const char *expr, size_t size, void *caller)
{
	char	log[H2_CAP];

	snprintf(log, sizeof log, "%s%s %s%s %s%zu bytes %sat %s%s\n", \
		RED, expr, YELLOW, "leaked", RED, size, GREY, \
		format_addr(caller), NONE
	);
	message_send(ctx->pipe, LOG, (t_message_data *)log);
}

static inline void	add_formatted_value(char *buff, size_t cap, size_t *offset, t_format fmt, intptr_t value)
{
	switch (fmt)
	{
		case F_BOOL:
			if (value == true) *offset+= snprintf(buff + *offset, cap - *offset, "true");
			else *offset+= snprintf(buff + *offset, cap - *offset, "false");
			break;
		case F_SIGNED:		*offset+= snprintf(buff + *offset, cap - *offset, "%" PRIdPTR, (intptr_t)value); break;
		case F_UNSIGNED:	*offset+= snprintf(buff + *offset, cap - *offset, "%" PRIuPTR, (uintptr_t)value); break;
		case F_CHAR:		*offset+= snprintf(buff + *offset, cap - *offset, "%c", (char)value); break;
		case F_STRING:		*offset+= snprintf(buff + *offset, cap - *offset, "%s", (char *)value); break;
		case F_STRUCT:		*offset+= snprintf(buff + *offset, cap - *offset, "unexpected struct content"); break;
		default:			*offset+= snprintf(buff + *offset, cap - *offset, "%" PRIxPTR, (uintptr_t)value); break;
	}
}
