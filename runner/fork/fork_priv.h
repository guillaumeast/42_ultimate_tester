#ifndef ULT_FORK_PRIV_H
#define ULT_FORK_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Internal header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "fork_pub.h"
#include "error_priv.h"
#include <sys/types.h>

t_error	fork_init(t_context *context, size_t timeout);
t_error	fork_init_parent(t_context *context);
t_error	fork_init_child(t_context *context);
void	fork_clear(t_context *context);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORK_PRIV_H */
