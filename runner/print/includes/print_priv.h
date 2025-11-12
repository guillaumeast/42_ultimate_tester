#ifndef ULT_PRINT_PRIV_H
# define ULT_PRINT_PRIV_H

# include "print_pub.h"
# include "set_priv.h"
# include <locale.h>
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

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*green;
	char	*yellow;
	char	*blue;
	char	*none;
}	t_colors;

typedef struct s_emojis
{
	char	*error;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

extern t_colors	colors;
extern t_emojis	emojis;

# define GREY	colors.grey
# define RED	colors.red
# define GREEN	colors.green
# define YELLOW	colors.yellow
# define BLUE	colors.blue
# define NONE	colors.none

# define EMJ_ERR		(emojis.error)
# define EMJ_SUC_START	(emojis.success_title_start)
# define EMJ_SUC_END	(emojis.success_title_end)
# define EMJ_FAIL_START	(emojis.fail_title_start)
# define EMJ_FAIL_END	(emojis.fail_title_end)

#define ult_err(fmt, ...) \
	ult_fprintf(ULT_STDERR, "%s %s Error: " fmt "%s\n", RED, EMJ_ERR, ##__VA_ARGS__, NONE)

void	print_set_title(const t_set *set);
void	print_set_result(const t_result *result);
void	print_result(const t_result *result);

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
	emojis.error =					isutf8 ? "❗️" : "✖";
	emojis.success_title_start =	isutf8 ? "🎉" : "✖";
	emojis.success_title_end =		isutf8 ? "🚀" : "✖";
	emojis.fail_title_start =		isutf8 ? "💥" : "✖";
	emojis.fail_title_end =			isutf8 ? "😈" : "✖";
}

#endif
