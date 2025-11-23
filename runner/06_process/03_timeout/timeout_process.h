#ifndef ULT_TIMEOUT_PROCESS_H
#define ULT_TIMEOUT_PROCESS_H

#ifndef __FUT_PROCESS_INSIDE__
/*
**  Private header for the PROCESS subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "context_pub.h"

void	timeout_init(t_context *context, size_t timeout);
void	timeout_start(t_context *context);
void	timeout_cancel(t_context *context);

#endif /* __FUT_PROCESS_INSIDE__ */

#endif /* ULT_TIMEOUT_PROCESS_H */
