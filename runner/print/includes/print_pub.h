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


//---------- PRINTER ---------//

void	ult_fprintf(t_ult_fd fd, const char *fmt, ...);

# define ult_print(fmt, ...) ult_fprintf(ULT_STDOUT, fmt "%s", ##__VA_ARGS__, NONE)
# define ult_print_err(fmt, ...) ult_fprintf(ULT_STDERR, fmt "%s", ##__VA_ARGS__, NONE)

#endif
