#include <stdbool.h>
#include <unistd.h>

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*bred;
	char	*green;
	char	*bgreen;
	char	*yellow;
	char	*blue;
	char	*bblue;
	char	*cyan;
	char	*none;
}	t_colors;

static t_colors	g_colors;
static bool		s_colors_initialized = false;

static inline void	colors_init(void);

// Generate getters
#define X_COLOR(color_name)							\
    const char *colors_get_##color_name(void)		\
	{												\
        if (!s_colors_initialized) colors_init();	\
        return g_colors.color_name;					\
    }
#include "colors.x"
#undef X_COLOR

static inline void	colors_init(void)
{
	bool		istty;

	istty = isatty(STDOUT_FILENO);
	g_colors.grey =		istty ? "\033[0;90m" : "";
	g_colors.red =		istty ? "\033[0;31m" : "";
	g_colors.bred =		istty ? "\033[1;31m" : "";
	g_colors.green =	istty ? "\033[0;32m" : "";
	g_colors.bgreen =	istty ? "\033[1;32m" : "";
	g_colors.yellow =	istty ? "\033[0;33m" : "";
	g_colors.blue =		istty ? "\033[0;34m" : "";
	g_colors.bblue =	istty ? "\033[1;34m" : "";
	g_colors.cyan =		istty ? "\033[1;36m" : "";
	g_colors.none =		istty ? "\033[0m" : "";
	s_colors_initialized = true;
}
