#include "print.h"
#include <stdio.h>

#define TITLE_MAX_LEN 29
#define SCORE_LEN 3
#define fzu(nb, var)													\
	char	var[(SCORE_LEN) + 1] = {0};									\
	snprintf(var, sizeof(var), "%*zu", (int)(SCORE_LEN), (size_t)(nb))

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

void	print_set_result(const t_result *result)
{
	t_colors	colors;

	fzu(result->passed, passed);
	fzu(result->failed, failed);
	fzu(result->timed, timed);
	fzu(result->crashed, crashed);
	get_colors(result, &colors);
	printf(" %s├-------┬-------┬-------┬-------┐%s\n", BLUE, NONE);
	printf(" %s|%s ✔ %s %s|%s ✖ %s %s|%s ⊘ %s %s|%s ☠ %s |%s\n", \
			BLUE, colors.passed, passed, BLUE, colors.failed, failed, \
			BLUE, colors.timed, timed, BLUE, colors.crashed, crashed, NONE);
	printf(" %s└-------┴-------┴-------┴-------┘%s\n", BLUE, NONE);
}

void	print_global_result(const t_result *result)
{
	t_colors	colors;

	fzu(result->passed, passed);
	fzu(result->failed, failed);
	fzu(result->timed, timed);
	fzu(result->crashed, crashed);
	get_colors(result, &colors);
	printf("\n %s┌-----------------------------------┐%s\n", colors.borders, NONE);
	if (result->total == result->passed)
		printf(" %s|          🎉 YOU WON! 🚀           |%s\n", colors.borders, NONE);
	else
		printf(" %s|          💥 TRY AGAIN 😈          |%s\n", colors.borders, NONE);
	printf(" %s├--------┬--------┬-------┬---------┤%s\n", colors.borders, NONE);
	printf(" %s|%s PASSED %s|%s FAILED %s|%s TIMED %s|%s CRASHED %s|%s\n", \
		colors.borders, colors.passed, colors.borders, colors.failed, \
		colors.borders, colors.timed, colors.borders, colors.crashed, colors.borders, NONE);
	printf(" %s├--------┼--------┼-------┼---------┤%s\n", colors.borders, NONE);
	printf(" %s|%s ✔  %s %s|%s ✖  %s %s|%s ⊘ %s %s|%s ☠   %s %s|%s\n", \
		colors.borders, colors.passed, passed, colors.borders, colors.failed, failed, \
		colors.borders, colors.timed, timed, colors.borders, colors.crashed, crashed, colors.borders, NONE);
	printf(" %s└--------┴--------┴-------┴---------┘%s\n", colors.borders, NONE);
}

void	get_colors(const t_result *result, t_colors *colors)
{
	if (!result || !colors)
		return ;
	colors->borders = GREY;
	colors->passed = GREY;
	colors->failed = GREY;
	colors->timed = GREY;
	colors->crashed = GREY;
	if (result->total == result->passed)
	{
		colors->borders = GREEN;
		colors->passed = GREEN;
	}
	else
		colors->borders = RED;
	if (result->failed > 0)
		colors->failed = RED;
	if (result->timed > 0)
		colors->timed = RED;
	if (result->crashed > 0)
		colors->crashed = RED;
}
