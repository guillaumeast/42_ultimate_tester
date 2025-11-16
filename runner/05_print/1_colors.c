#include <stdbool.h>
#include <unistd.h>

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*green;
	char	*yellow;
	char	*blue;
	char	*none;
}	t_colors;

static t_colors	g_colors;
static bool		g_colors_initialized = false;

static inline void	colors_init(void);

// Generate getters
#define X_COLOR(color_name)							\
    const char *print_color_##color_name(void)		\
	{												\
        if (!g_colors_initialized) colors_init();	\
        return g_colors.color_name;					\
    }
#include "colors.x"
#undef X_COLOR

static inline void	colors_init(void)
{
	bool		istty;

	istty = isatty(STDOUT_FILENO);
	g_colors.grey =		istty ? "\033[90m" : "";
	g_colors.red =		istty ? "\033[31m" : "";
	g_colors.green =	istty ? "\033[32m" : "";
	g_colors.yellow =	istty ? "\033[33m" : "";
	g_colors.blue =		istty ? "\033[34m" : "";
	g_colors.none =		istty ? "\033[00m" : "";
	g_colors_initialized = true;
}
