#include <locale.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_emojis
{
	char	*arrow_down_right;
	char	*arrow_right;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed_y;
	char	*crashed_n;
	char	*error;
	char	*test;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

static t_emojis	g_emojis;
static bool		g_emojis_initialized = false;

static inline void	emojis_init(void);

// Generate getters
#define X_EMOJI(emoji_name)						\
    const char *print_emoji_##emoji_name(void)		\
	{												\
        if (!g_emojis_initialized) emojis_init();	\
        return g_emojis.emoji_name;					\
    }
#include "emojis.x"
#undef X_EMOJI

static inline void	emojis_init(void)
{
	bool		isutf8;
	const char	*locale;

	setlocale(LC_CTYPE, "");
	locale = setlocale(LC_CTYPE, NULL);
	isutf8 = locale && strstr(locale, "UTF-8");
	g_emojis.arrow_down_right =			isutf8 ? "⤷" : ">";
	g_emojis.arrow_right =				isutf8 ? "➜" : ">";
	g_emojis.passed =					isutf8 ? "✔ " : "v";
	g_emojis.failed =					isutf8 ? "✖ " : "x";
	g_emojis.timed =					isutf8 ? "⏱ " : "t";
	g_emojis.crashed_y =				isutf8 ? "💥" : "c";
	g_emojis.crashed_n =				isutf8 ? "☠ " : "c";
	g_emojis.error =					isutf8 ? "❗️" : "e";
	g_emojis.test =						isutf8 ? "🧪" : " ";
	g_emojis.success_title_start =		isutf8 ? "🎉" : " ";
	g_emojis.success_title_end =		isutf8 ? "🚀" : " ";
	g_emojis.fail_title_start =			isutf8 ? "💥" : " ";
	g_emojis.fail_title_end =			isutf8 ? "😈" : " ";
}
