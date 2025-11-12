#ifndef ULT_PRINT_PRIV_H
# define ULT_PRINT_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "print_pub.h"
# include "set_priv.h"
# include "assert_pub.h"
# include <locale.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

typedef struct s_tab_colors
{
	char	*borders;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed;
}	t_tab_colors;

typedef struct s_emojis
{
	char	*arrow_down_right;
	char	*arrow_right;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed;
	char	*error;
	char	*test;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

extern t_emojis	emojis;

# define EMJ_ARW_DR		(emojis.arrow_down_right)
# define EMJ_ARW_RIGHT	(emojis.arrow_right)
# define EMJ_PASS		(emojis.passed)
# define EMJ_FAIL		(emojis.failed)
# define EMJ_TIMD		(emojis.timed)
# define EMJ_CRSH		(emojis.crashed)
# define EMJ_ERR		(emojis.error)
# define EMJ_TEST		(emojis.test)
# define EMJ_SUC_START	(emojis.success_title_start)
# define EMJ_SUC_END	(emojis.success_title_end)
# define EMJ_FAIL_START	(emojis.fail_title_start)
# define EMJ_FAIL_END	(emojis.fail_title_end)

void	print_start(void);
void	print_set_title(const t_set *set);
void	print_set_passed(const t_set *set);
void	print_set_timed(void);
void	print_set_crashed(void);
void	print_assert_failed(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);
void	print_result(const t_result *result);

#define ult_err(fmt, ...) \
	ult_fprintf(ULT_STDERR, "%s %s Error: " fmt "%s\n", RED, EMJ_ERR, ##__VA_ARGS__, NONE)
#define print_set_start(set)  do { print_set_title(set); ultprint("\n"); } while (0)

static inline void	print_init_format()
{
	bool		istty;
	bool		isutf8;
	const char	*locale;

	istty = isatty(STDOUT_FILENO);
	colors.grey =	istty ? "\033[90m" : "";
	colors.red =	istty ? "\033[31m" : "";
	colors.green =	istty ? "\033[32m" : "";
	colors.yellow =	istty ? "\033[33m" : "";
	colors.blue =	istty ? "\033[34m" : "";
	colors.none =	istty ? "\033[0m" : "";

	setlocale(LC_CTYPE, "");
	locale = setlocale(LC_CTYPE, NULL);
	isutf8 = locale && strstr(locale, "UTF-8");
	emojis.arrow_down_right =		isutf8 ? "⤷" : ">";
	emojis.arrow_right =			isutf8 ? "➜" : ">";
	emojis.passed =					isutf8 ? "✔" : "[PASS]";
	emojis.failed =					isutf8 ? "✖" : "[FAIL]";
	emojis.timed =					isutf8 ? "⏱" : "[TIMD]";
	emojis.crashed =				isutf8 ? "💥" : "[CRSH]";
	emojis.error =					isutf8 ? "❗️" : "[!ERR]";
	emojis.test =					isutf8 ? "🧪" : " ";
	emojis.success_title_start =	isutf8 ? "🎉" : " ";
	emojis.success_title_end =		isutf8 ? "🚀" : " ";
	emojis.fail_title_start =		isutf8 ? "💥" : " ";
	emojis.fail_title_end =			isutf8 ? "😈" : " ";
}

#endif
