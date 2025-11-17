#define __FUT_INSIDE__
#define __FUT_PRINT_INSIDE__
#include "print_priv.h"
#undef __FUT_PRINT_INSIDE__
#undef __FUT_INSIDE__

#include <stdio.h>

#define BUFF_SIZE 256

typedef struct s_set_colors
{
	const char	*start;
	const char	*emoji;
	const char	*passed;
	const char	*failed;
	const char	*timed;
	const char	*crashed;
}	t_set_colors;

static inline void	get_colors(const t_result *res, t_set_colors *colors);

void	print_set_title(const t_set *set)
{
	print_stdout("%s%s %sTesting %s%s%s...\n", BLUE, EMJ_ARW_RIGHT, NONE, BLUE, set->name, NONE);
}

void	print_set_result(const t_set *set)
{
	const t_result	*res;
	t_set_colors	colors;
	char			buff[BUFF_SIZE];
	size_t			i;

	res = &set->result;
	get_colors(res, &colors);

	i = 0;
	i += snprintf(buff + i, sizeof(buff) - i, \
		"     %s%s %s%s ", colors.start, EMJ_ARW_DR, colors.emoji, NONE);
	i += snprintf(buff + i, sizeof(buff) - i, \
		"%sPASSED: %zu %s|%s ", colors.passed, res->passed, GREY, NONE);
	i += snprintf(buff + i, sizeof(buff) - i, \
		"%sFAILED: %zu %s|%s ", colors.failed, res->failed, GREY, NONE);
	i += snprintf(buff + i, sizeof(buff) - i, \
		"%sTIMED: %zu %s|%s ", colors.timed, res->timed, GREY, NONE);
	i += snprintf(buff + i, sizeof(buff) - i, \
		"%sCRASHED: %zu%s\n", colors.crashed, res->crashed, NONE);
	print_stdout(buff);
}

static inline void	get_colors(const t_result *res, t_set_colors *colors)
{
	if (res->passed == res->total)
	{
		colors->start = GREEN;
		colors->emoji = EMJ_PASS;
	}
	else
	{
		colors->start = RED;
		colors->emoji = EMJ_FAIL;
	}
	colors->passed =	res->passed	> 0 ? GREEN : GREY;
	colors->failed =	res->failed	> 0 ? RED : GREY;
	colors->timed =		res->timed	> 0 ? RED : GREY;
	colors->crashed =	res->crashed	> 0 ? RED : GREY;
}
