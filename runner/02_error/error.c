#define __FUT_INSIDE__
#include "error_priv.h"
#include "colors_priv.h"
#include "emojis_priv.h"
#include "print_wrapper_pub.h"
#undef __FUT_INSIDE__

#include <stdlib.h>

#define MAX_ERR_COUNT 256

static const char *error_names[] =
{
#define X_ERROR(name) #name,
#include "error.x"
# undef X_ERROR
};

static	t_error	s_error_trace[MAX_ERR_COUNT];
static	size_t	s_error_count = 0;

void	error_log(t_error error)
{
	if (error == NO_ERROR)
		return ;

	s_error_trace[s_error_count] = error;
	s_error_count++;
	exit_if(s_error_count == MAX_ERR_COUNT, TOO_MANY_ERRORS);
}

void	error_reset_trace(void)
{
	size_t	i;

	i = 0;
	while (i < s_error_count)
		s_error_trace[i++] = NO_ERROR;
	s_error_count = 0;
}

void	error_print_trace(void)
{
	int		i;
	t_error	error;

	if (s_error_count == 0)
		return ;

	i = s_error_count;
	while(--i >= 0)
	{
		error = s_error_trace[i];
		print_stderr(" %s%s %s%s", YELLOW, EMJ_ARW_RIGHT, error_names[error], NONE);
	}
}

void	exit_if(bool condition, t_error error)
{
	if (!condition)
		return ;

	error_log(error);
	print_stderr(" %s%s Internal error%s", RED, EMJ_ERR, NONE);
	error_print_trace();
	print_stderr("Please try again or report the issue\n");

	exit(100 + error);
}
