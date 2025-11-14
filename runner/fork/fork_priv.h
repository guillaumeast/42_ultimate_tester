#ifndef ULT_FORK_PRIV_H
# define ULT_FORK_PRIV_H

#ifdef __FUT_H_INSIDE__
# error "Do not include this file directly. Use <ft_ultimate_tester.h> instead."
#endif

# include "fork_pub.h"
# include "error_pub.h"
# include <sys/types.h>

t_error	fork_init(t_context *context, size_t timeout);
t_error	fork_init_parent(t_context *context);
t_error	fork_init_child(t_context *context);
void	fork_clear(t_context *context);

#endif
