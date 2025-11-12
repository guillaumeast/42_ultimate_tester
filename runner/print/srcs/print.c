#include "print_priv.h"
#include "redirect_priv.h"
#include <inttypes.h>
#include <stdarg.h>

#define TITLE_MAX_LEN 29
#define SCORE_LEN 3
#define size_t_to_string(nb, var)										\
	char	var[(SCORE_LEN) + 1] = {0};									\
	snprintf(var, sizeof(var), "%*zu", (int)(SCORE_LEN), (size_t)(nb))

static inline void	get_tab_colors(const t_result *result, t_tab_colors *tab_colors);

t_colors	colors;
t_emojis	emojis;

__attribute__((format(printf, 2, 3)))
void	ult_fprintf(t_ult_fd fd, const char *fmt, ...)
{
	va_list	args;
	int		target_fd;

	if (fd == ULT_STDOUT)
		target_fd = g_output.real_stdout_fd;
	else
	 	target_fd = g_output.real_stderr_fd;

	va_start(args, fmt);
	vdprintf(target_fd, fmt, args);
	va_end(args);
}

void	print_start(void)
{
	char	title[TITLE_MAX_LEN + 1];

	snprintf(title, sizeof(title), "%s %s", EMJ_TEST, " Running tests...");
	size_t len = strlen(title);
	memset(title + len, ' ', sizeof(title) - len - 1);
	title[sizeof(title) - 1] = '\0';
	_ult_print(" %s┌-------------------------------┐%s\n", BLUE, NONE);
	_ult_print(" %s| %s   |%s\n", BLUE, title, NONE);
	_ult_print(" %s├-------------------------------┘%s\n", BLUE, NONE);
}

// TODO: do a macro instead ?
void	print_set_title(const t_set *set)
{
	_ult_print(" %s| %s %sTesting %s%s%s...\n", BLUE, EMJ_ARW_RIGHT, NONE, BLUE, set->name, NONE);
}

// TODO: do a macro instead ?
void	print_set_passed(const t_set *set)
{
	_ult_print(" %s|%s     %s %s PASSED%s", BLUE, GREEN, EMJ_ARW_DR, EMJ_PASS, GREY);
	_ult_print("%s [%s%zu%s]%s\n", GREY, GREEN, set->result.passed, GREY, NONE);
}

void	print_set_failed(const t_set *set)
{
	_ult_print(" %s|%s     %s %s FAILED%s", BLUE, RED, EMJ_ARW_DR, EMJ_FAIL, GREY);
	_ult_print("%s [%s%zu / %zu%s]%s\n", GREY, RED, set->result.passed, set->result.total, GREY, NONE);
}

// TODO: do a macro instead ?
void	print_set_timed(void)
{
	ult_fprintf(ULT_STDERR, " %s|     %s⤷ %s TIMED OUT%s\n", BLUE, RED, EMJ_TIMD, NONE);
}

// TODO: do a macro instead ?
void	print_set_crashed(void)
{
	ult_fprintf(ULT_STDERR, " %s|     %s⤷ %s CRASHED%s\n", BLUE, RED, EMJ_CRSH, NONE);
}

// TODO: do a macro instead ?
void	print_assert_failed(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt)
{
	const char	*format;

	if (fmt == F_SIGNED)		format = "%" PRIdPTR;
	else if (fmt == F_UNSIGNED)	format = "%" PRIuPTR;
	else if (fmt == F_HEX)		format = "%" PRIxPTR;
	else if (fmt == F_CHAR)		format = "%c";
	else if (fmt == F_STRING)	format = "%s";
	else						format = "%" PRIxPTR;

	ult_fprintf(ULT_STDERR, " %s|%s     %s %s %s%s %s=%s ", BLUE, RED, EMJ_ARW_DR, EMJ_FAIL, YELLOW, name, NONE, RED);
	ult_fprintf(ULT_STDERR, format, got);
	if (eq)
		ult_fprintf(ULT_STDERR, "%s (expected %s", NONE, RED);
	else
		ult_fprintf(ULT_STDERR, "%s (expected != %s", NONE, RED);
	ult_fprintf(ULT_STDERR, format, exp);
	ult_fprintf(ULT_STDERR, "%s)\n", NONE);
}

void	print_result(const t_result *result)
{
	t_tab_colors	tab_colors;
	t_ult_fd		fd;

	size_t_to_string(result->passed, passed);
	size_t_to_string(result->failed, failed);
	size_t_to_string(result->timed, timed);
	size_t_to_string(result->crashed, crashed);
	get_tab_colors(result, &tab_colors);
	if (result->passed == result->total)
		fd = ULT_STDOUT;
	else
		fd = ULT_STDERR;
	ult_fprintf(fd, " %s├-----------------------------------┐%s\n", tab_colors.borders, NONE);
	if (result->total == result->passed)
		ult_fprintf(fd, " %s|          %s YOU WON! %s           |%s\n", \
			tab_colors.borders, EMJ_SUC_START, EMJ_SUC_END, NONE);
	else
		ult_fprintf(fd, " %s|          %s TRY AGAIN %s          |%s\n", \
			tab_colors.borders, EMJ_FAIL_START, EMJ_FAIL_END, NONE);
	ult_fprintf(fd, " %s├--------┬--------┬-------┬---------┤%s\n", tab_colors.borders, NONE);
	ult_fprintf(fd, " %s|%s PASSED %s|%s FAILED %s|%s TIMED %s|%s CRASHED %s|%s\n", \
		tab_colors.borders, tab_colors.passed, tab_colors.borders, \
		tab_colors.failed, tab_colors.borders, tab_colors.timed, \
		tab_colors.borders, tab_colors.crashed, tab_colors.borders, NONE);
	ult_fprintf(fd, " %s├--------┼--------┼-------┼---------┤%s\n", tab_colors.borders, NONE);
	ult_fprintf(fd, " %s|%s %s %s %s|%s %s %s %s|%s %s%s %s|%s %s  %s %s|%s\n", \
		tab_colors.borders, tab_colors.passed, EMJ_PASS, passed, tab_colors.borders, \
		tab_colors.failed, EMJ_FAIL, failed, tab_colors.borders, tab_colors.timed, \
		EMJ_TIMD, timed, tab_colors.borders, tab_colors.crashed, EMJ_CRSH, crashed, tab_colors.borders, NONE);
	ult_fprintf(fd, " %s└--------┴--------┴-------┴---------┘%s\n", tab_colors.borders, NONE);
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
