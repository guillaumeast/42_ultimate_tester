#ifndef ULT_SET_PRIV_H
# define ULT_SET_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "set_pub.h"
# include <stddef.h>

typedef struct s_result
{
	size_t		total;
	size_t		passed;
	size_t		failed;
	size_t		timed;
	size_t		crashed;
}	t_result;

extern t_result	g_result;

void	run_set(t_set *set);

#endif
