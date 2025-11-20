#ifndef ULT_STACKTRACE_IPC_H
#define ULT_STACKTRACE_IPC_H

#ifndef __FUT_IPC_INSIDE__
/*
**  Private header for the IPC subsystem.
**  Not available outside its compilation unit.
*/
#else

#include "stacktrace_priv.h"
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>

void	stacktrace_init(void);

#endif /* __FUT_INSIDE__ */

#endif /* ULT_STACKTRACE_IPC_H */
