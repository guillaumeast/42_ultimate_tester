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
	char	*leaked;
	char	*error;
	char	*test;
	char	*success_title_start;
	char	*success_title_end;
	char	*fail_title_start;
	char	*fail_title_end;
}	t_emojis;

static t_emojis	g_emojis;
static bool		s_emojis_initialized = false;

static inline void	emojis_init(void);

// Generate getters
#define X_EMOJI(emoji_name)							\
    const char *emojis_get_##emoji_name(void)		\
	{												\
        if (!s_emojis_initialized) emojis_init();	\
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
	g_emojis.arrow_down_right =			isutf8 ? "⤷ " : "> ";
	g_emojis.arrow_right =				isutf8 ? "➜ " : "> ";
	g_emojis.passed =					isutf8 ? "✔ " : "V ";
	g_emojis.failed =					isutf8 ? "✖ " : "X ";
	g_emojis.timed =					isutf8 ? "⏱ " : "T ";
	g_emojis.crashed_y =				isutf8 ? "💥 " : "C ";
	g_emojis.crashed_n =				isutf8 ? "☠ " : "C ";
	g_emojis.leaked =					isutf8 ? "💧 " : "L ";
	g_emojis.error =					isutf8 ? "❗️" : "E ";
	g_emojis.test =						isutf8 ? "🧪" : " ";
	g_emojis.success_title_start =		isutf8 ? "🎉" : " ";
	g_emojis.success_title_end =		isutf8 ? "🚀" : " ";
	g_emojis.fail_title_start =			isutf8 ? "💥" : " ";
	g_emojis.fail_title_end =			isutf8 ? "😈" : " ";
}
