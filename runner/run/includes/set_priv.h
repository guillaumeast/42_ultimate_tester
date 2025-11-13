#ifndef ULT_SET_PRIV_H
# define ULT_SET_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "error_pub.h"
# include "set_pub.h"
# include <stdbool.h>
# include <stddef.h>

extern t_result	g_result;
extern t_set	*g_current_set;

t_error	run_set(t_set *set);

#endif
