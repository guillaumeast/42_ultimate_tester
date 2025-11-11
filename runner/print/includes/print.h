#ifndef ULT_PRINT_H
# define ULT_PRINT_H

# include "set.h"

# define GREY "\033[90m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define NONE "\033[0m"

typedef struct s_colors
{
	char	*borders;
	char	*passed;
	char	*failed;
	char	*timed;
	char	*crashed;
}	t_colors;

void	print_set_title(const t_set *set);
void	print_set_result(const t_result *result);
void	print_global_result(const t_result *result);
void	get_colors(const t_result *result, t_colors *colors);

#endif
