#define __FUT_INSIDE__
#include "error_priv.h"
#include "print_priv.h"
#undef __FUT_INSIDE__

#include <stdlib.h>

#define MAX_ERR_COUNT 256

static const char *error_names[] =
{
#define X_ERROR(name) #name,
#include "error.x"
# undef X_ERROR
};

static	t_error	g_error_trace[MAX_ERR_COUNT];
static	size_t	g_error_count = 0;

bool	error_log(t_error error)
{
	if (error == NO_ERROR)
		return (true);

	g_error_trace[g_error_count] = error;
	g_error_count++;
	exit_if(g_error_count == MAX_ERR_COUNT);

	return (false);
}

void	error_reset_trace(void)
{
	size_t	i;

	i = 0;
	while (i < g_error_count)
		g_error_trace[i++] = NO_ERROR;
	g_error_count = 0;
}

void	error_print_trace(void)
{
	int		i;
	t_error	error;

	if (g_error_count == 0)
		return ;

	i = g_error_count;
	while(--i >= 0)
	{
		error = g_error_trace[i];
		print_stderr("%s %s %s%s\n", RED, EMJ_ARW_DR, error_names[error], NONE);
	}
}

void	exit_if(bool condition)
{
	int	exit_code;

	if (!condition)
		return;

	print_stderr("%s %s Internal error:%s\n", RED, EMJ_ERR, NONE);
	error_print_trace();
	print_stderr(" %s Please try again or report the issue\n", EMJ_ARW_RIGHT);

	exit_code = g_error_count > 0 \
		? 100 + g_error_trace[g_error_count - 1] \
		: 1;
	exit(exit_code);
}
