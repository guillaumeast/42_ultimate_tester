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

void	print_start(void);
void	print_result(const t_result *result);

// TODO: param t_assert *assert instead of this big list
void	print_assert_failed(bool eq, const char *name, intptr_t got, intptr_t exp, t_format fmt);

void	print_set_title(const t_set *set);
void	print_set_passed(const t_set *set);
void	print_set_failed(const t_set *set);
void	print_set_timed(void);
void	print_set_crashed(void);

# define _ult_print(fmt, ...) ult_fprintf(ULT_STDOUT, fmt "%s", ##__VA_ARGS__, NONE)
# define _ult_print_err(fmt, ...) ult_fprintf(ULT_STDERR, fmt "%s", ##__VA_ARGS__, NONE)

static inline void	init_print_format()
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
	emojis.passed =					isutf8 ? "✔ " : "v";
	emojis.failed =					isutf8 ? "✖ " : "x";
	emojis.timed =					isutf8 ? "⏱ " : "t";
	emojis.crashed_y =				isutf8 ? "💥" : "c";
	emojis.crashed_n =				isutf8 ? "☠ " : "c";
	emojis.error =					isutf8 ? "❗️" : "e";
	emojis.test =					isutf8 ? "🧪" : " ";
	emojis.success_title_start =	isutf8 ? "🎉" : " ";
	emojis.success_title_end =		isutf8 ? "🚀" : " ";
	emojis.fail_title_start =		isutf8 ? "💥" : " ";
	emojis.fail_title_end =			isutf8 ? "😈" : " ";
}

#endif
