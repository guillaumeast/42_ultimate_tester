#ifndef ULTIMATE_PREBUILD_TYPES_H
# define ULTIMATE_PREBUILD_TYPES_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>


typedef struct s_string
{
	char	*data;
	size_t	len;
}	t_string;

typedef struct s_target
{
	t_string	raw;	// Try(...)
	t_string	start;	// Try(
}	t_target;

typedef struct s_run
{
	t_target	target;
	t_string	template;
	t_string	tmp_template;
	t_string	input;
	char		*output_path;
}	t_run;

#endif
