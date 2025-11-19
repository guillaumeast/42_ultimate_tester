#ifndef ULT_FORK_PRIV_H
#define ULT_FORK_PRIV_H

#ifndef __FUT_INSIDE__
/*
**  Private header for the FUT modules.
**  Not available outside its compilation unit.
*/
#else

#include "fork_pub.h"

void	fork_cleanup(t_context *context);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_FORK_PRIV_H */
