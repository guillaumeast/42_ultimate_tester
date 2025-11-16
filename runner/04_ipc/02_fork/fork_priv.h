#ifndef ULT_FORK_PRIV_H
#define ULT_FORK_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "fork_pub.h"

void	fork_init(t_context *context, size_t timeout);
void	fork_init_parent(t_context *context);
void	fork_init_child(t_context *context);
void	fork_clear(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORK_PRIV_H */
