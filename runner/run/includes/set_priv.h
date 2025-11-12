#ifndef ULT_SET_PRIV_H
# define ULT_SET_PRIV_H

# include "set_pub.h"

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

void	run_set(t_set *set);

extern t_result	g_result;

#endif
