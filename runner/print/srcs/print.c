#include "print_priv.h"
#include "redirect_priv.h"
#include <stdarg.h>

#define TITLE_MAX_LEN 29
#define SCORE_LEN 3
#define size_t_to_string(nb, var)										\
	char	var[(SCORE_LEN) + 1] = {0};									\
	snprintf(var, sizeof(var), "%*zu", (int)(SCORE_LEN), (size_t)(nb))

static inline void	get_tab_colors(const t_result *result, t_tab_colors *tab_colors);

/*-------------- TODO SECTION (START) --------------*/

// TODO: update all printf()/fprintf() calls to ult_fprintf() calls

// Make it visible to user
void	ult_fprintf(t_ult_fd fd, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	if (fd == ULT_STDOUT)
		vdprintf(g_output.real_stdout_fd, fmt, args);
	else
		vdprintf(g_output.real_stderr_fd, fmt, args);
	va_end(args);
}

void	print_set_title(const t_set *set)
{
	char	title[TITLE_MAX_LEN + 1];
	size_t	i;

	i = 0;
	while (i < TITLE_MAX_LEN && set->name[i])
	{
		title[i] = set->name[i];
		i++;
	}
	while (i < TITLE_MAX_LEN)
		title[i++] = ' ';
	title[i] = '\0';
	printf(" %s┌-------------------------------┐%s\n", BLUE, NONE);
	printf(" %s|%s %s %s|%s\n", BLUE, BLUE, title, BLUE, NONE);
	printf(" %s├-------------------------------┘%s\n", BLUE, NONE);
}

void	print_result(const t_result *result)
{
	t_tab_colors	tab_colors;

	size_t_to_string(result->passed, passed);
	size_t_to_string(result->failed, failed);
	size_t_to_string(result->timed, timed);
	size_t_to_string(result->crashed, crashed);
	get_tab_colors(result, &tab_colors);
	printf("\n %s┌-----------------------------------┐%s\n", tab_colors.borders, NONE);
	if (result->total == result->passed)
		printf(" %s|          %s YOU WON! %s           |%s\n", \
			tab_colors.borders, EMJ_SUC_START, EMJ_SUC_END, NONE);
	else
		printf(" %s|          %s TRY AGAIN %s          |%s\n", \
			tab_colors.borders, EMJ_FAIL_START, EMJ_FAIL_END, NONE);
	printf(" %s├--------┬--------┬-------┬---------┤%s\n", tab_colors.borders, NONE);
	printf(" %s|%s PASSED %s|%s FAILED %s|%s TIMED %s|%s CRASHED %s|%s\n", \
		tab_colors.borders, tab_colors.passed, tab_colors.borders, \
		tab_colors.failed, tab_colors.borders, tab_colors.timed, \
		tab_colors.borders, tab_colors.crashed, tab_colors.borders, NONE);
	printf(" %s├--------┼--------┼-------┼---------┤%s\n", tab_colors.borders, NONE);
	printf(" %s|%s ✔  %s %s|%s ✖  %s %s|%s ⊘ %s %s|%s ☠   %s %s|%s\n", \
		tab_colors.borders, tab_colors.passed, passed, tab_colors.borders, \
		tab_colors.failed, failed, tab_colors.borders, tab_colors.timed, \
		timed, tab_colors.borders, tab_colors.crashed, crashed, tab_colors.borders, NONE);
	printf(" %s└--------┴--------┴-------┴---------┘%s\n", tab_colors.borders, NONE);
}

static inline void	get_tab_colors(const t_result *result, t_tab_colors *tab_colors)
{
	if (!result || !tab_colors)
		return ;
	tab_colors->borders = GREY;
	tab_colors->passed = GREY;
	tab_colors->failed = GREY;
	tab_colors->timed = GREY;
	tab_colors->crashed = GREY;
	if (result->total == result->passed)
	{
		tab_colors->borders = GREEN;
		tab_colors->passed = GREEN;
	}
	else
		tab_colors->borders = RED;
	if (result->failed > 0)
		tab_colors->failed = RED;
	if (result->timed > 0)
		tab_colors->timed = RED;
	if (result->crashed > 0)
		tab_colors->crashed = RED;
}

/*-------------- TODO SECTION (END) --------------*/
