#ifndef ULT_SET_PRIV_H
# define ULT_SET_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "error_pub.h"
# include "set_pub.h"
# include <stdbool.h>
# include <stddef.h>

extern t_set	g_set;
extern t_result	g_result;

t_error	set_run(t_set *set);

#endif
