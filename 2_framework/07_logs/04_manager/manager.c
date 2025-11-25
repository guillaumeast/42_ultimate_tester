#define __FUT_INSIDE__
#define __FUT_LOGS_INSIDE__
#include "error_priv.h"
#include "format_logs.h"
#include "print_wrapper_pub.h"
#include "status_pub.h"
#undef __FUT_LOGS_INSIDE__
#undef __FUT_INSIDE__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define H2_STORE_INITIAL_CAP 128
#define H2_STORE_GROWTH_RATIO 2

static char		**h2_stored_logs = NULL;
static size_t	h2_store_cap = 0;
static size_t	h2_store_count = 0;

static inline void	init_h2_storage(void);

void	logs_print_h1(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	print_stdout("%s", format_h1(fmt, args));
	va_end(args);
}

void	logs_print_indicator(t_status *status)
{
	print_stdout("%s", format_indicator(status));
}

void	logs_store_h2(const char *fmt, ...)
{
	va_list	args;
	char	*log;

	init_h2_storage();

	log = malloc(H2_CAP);
	exit_if(!log, NOT_ENOUGH_MEMORY);

	va_start(args, fmt);
	snprintf(log, H2_CAP, "%s", format_h2(fmt, args));
	va_end(args);

	h2_stored_logs[h2_store_count] = log;
	h2_store_count++;
}

void	logs_print_h2(void)
{
	print_stdout("\n");
	for (size_t i = 0; i < h2_store_count; i++)
	{
		print_stdout("%s", h2_stored_logs[i]);
		free(h2_stored_logs[i]);
	}
	free(h2_stored_logs);
	h2_stored_logs = NULL;
	h2_store_count = 0;
	h2_store_cap = 0;
}

static inline void	init_h2_storage(void)
{
	size_t	new_cap;
	char	**new_ptr;

	if (h2_store_cap == 0)
	{
		h2_stored_logs = malloc(H2_STORE_INITIAL_CAP * sizeof h2_stored_logs);
		exit_if(!h2_stored_logs, NOT_ENOUGH_MEMORY);
		h2_store_cap = H2_STORE_INITIAL_CAP;
	}
	else if (h2_store_count == h2_store_cap)
	{
		new_cap = h2_store_cap * 2;
		new_ptr = realloc(h2_stored_logs, new_cap * sizeof h2_stored_logs);
		exit_if(!new_ptr, NOT_ENOUGH_MEMORY);
		h2_stored_logs = new_ptr;
		h2_store_cap = new_cap;
	}
}
