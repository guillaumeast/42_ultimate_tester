#define __FUT_INSIDE__
#define __FUT_RESULT_INSIDE__
#include "colors_priv.h"
#include "emojis_priv.h"
#undef __FUT_RESULT_INSIDE__
#include "result_pub.h"
#undef __FUT_INSIDE__

#include <stdio.h>
#include <string.h>

#define START_TITLE_MAX_LEN 29
#define RES_TITLE_BUFF_SIZE 256
#define SEPARATOR_BUFF_SIZE 16
#define SCORE_BUFF_SIZE 64
#define SCORE_DIGITS 3

// TODO: add leaks handling

typedef struct s_res_colors
{
	const char	*borders;
	const char	*passed;
	const char	*failed;
	const char	*timed;
	const char	*crashed;
}	t_res_colors;

typedef struct s_res_content
{
	char	title[RES_TITLE_BUFF_SIZE];
	char	separator[SEPARATOR_BUFF_SIZE];
	char	passed[SCORE_BUFF_SIZE];
	char	failed[SCORE_BUFF_SIZE];
	char	timed[SCORE_BUFF_SIZE];
	char	crashed[SCORE_BUFF_SIZE];
}	t_res_content;

static inline void	get_colors(const t_result *res, t_res_colors *colors);
static inline void	get_content(const t_result *res, t_res_colors *colors, t_res_content *cont);

void	print_report(const t_result *result)
{
	t_res_content	content;
	t_res_colors	colors;

	get_colors(result, &colors);
	get_content(result, &colors, &content);

	printf(" %s├-----------------------------------┐%s\n", colors.borders, NONE);
	printf("%s\n", content.title);
	printf(" %s├--------┬--------┬-------┬---------┤%s\n", colors.borders, NONE);
	printf(" %s %sPASSED %s %sFAILED %s %sTIMED %s %sCRASHED %s\n", \
		content.separator, colors.passed, content.separator, colors.failed, \
		content.separator, colors.timed, content.separator, colors.crashed, content.separator);
	printf(" %s├--------┼--------┼-------┼---------┤%s\n", colors.borders, NONE);
	printf(" %s %s %s %s\n", content.passed, content.failed, content.timed, content.crashed);
	printf(" %s└--------┴--------┴-------┴---------┘%s\n", colors.borders, NONE);
}

static inline void	get_colors(const t_result *res, t_res_colors *col)
{
	col->borders = res->total == res->passed ? GREEN : RED;
	col->passed = res->passed > 0 ? GREEN : GREY;
	col->failed = res->failed > 0 ? RED : GREY;
	col->timed = res->timed > 0 ? RED : GREY;
	col->crashed = res->crashed > 0 ? RED : GREY;
}

static inline void	get_content(const t_result *res, t_res_colors *colors, t_res_content *cont)
{
	if (res->passed == res->total)
		sprintf(cont->title, " %s|          %s YOU WON! %s           |%s", \
			colors->borders, EMJ_SUC_START, EMJ_SUC_END, NONE);
	else
		sprintf(cont->title, " %s|          %s TRY AGAIN %s          |%s", \
			colors->borders, EMJ_FAIL_START, EMJ_FAIL_END, NONE);

	sprintf(cont->separator, "%s%c%s", colors->borders, '|', NONE);

	sprintf(cont->passed, "%s %s%s  %*zu%s", cont->separator, \
		colors->passed, EMJ_PASS, SCORE_DIGITS, res->passed, NONE);
	sprintf(cont->failed, "%s %s%s  %*zu%s", cont->separator, \
		colors->failed, EMJ_FAIL, SCORE_DIGITS, res->failed, NONE);
	sprintf(cont->timed, "%s %s%s %*zu%s", cont->separator, \
		colors->timed, EMJ_TIMD, SCORE_DIGITS, res->timed, NONE);
	sprintf(cont->crashed, "%s %s%s   %*zu %s", cont->separator, \
		colors->crashed, EMJ_CRSH, SCORE_DIGITS, res->crashed, cont->separator);
}
