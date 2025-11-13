#ifndef ULT_PRINT_PUB_H
# define ULT_PRINT_PUB_H

# include "redirect_pub.h"

//---------- COLORS ----------//

typedef struct s_colors
{
	char	*grey;
	char	*red;
	char	*green;
	char	*yellow;
	char	*blue;
	char	*none;
}	t_colors;

extern t_colors	colors;

# define GREY	colors.grey
# define RED	colors.red
# define GREEN	colors.green
# define YELLOW	colors.yellow
# define BLUE	colors.blue
# define NONE	colors.none

//---------- EMOJIS ----------//

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

extern t_emojis	emojis;

# define EMJ_ARW_DR		(emojis.arrow_down_right)
# define EMJ_ARW_RIGHT	(emojis.arrow_right)
# define EMJ_PASS		(emojis.passed)
# define EMJ_FAIL		(emojis.failed)
# define EMJ_TIMD		(emojis.timed)
# define EMJ_CRSH_Y		(emojis.crashed_y)
# define EMJ_CRSH_N		(emojis.crashed_n)
# define EMJ_ERR		(emojis.error)
# define EMJ_TEST		(emojis.test)
# define EMJ_SUC_START	(emojis.success_title_start)
# define EMJ_SUC_END	(emojis.success_title_end)
# define EMJ_FAIL_START	(emojis.fail_title_start)
# define EMJ_FAIL_END	(emojis.fail_title_end)

//---------- PRINTER ---------//

void	ult_fprintf(t_ult_fd fd, const char *fmt, ...);

# define ult_print(fmt, ...) \
	ult_fprintf(ULT_STDOUT, "%s | %s" fmt "%s", BLUE, NONE, ##__VA_ARGS__, NONE)
# define ult_print_err(fmt, ...) \
	ult_fprintf(ULT_STDERR, "%s | %s" fmt "%s", BLUE, NONE, ##__VA_ARGS__, NONE)

#endif
